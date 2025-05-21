#include "../../include/services/TicketService.h"

 TicketService::TicketService(RepositoryRegistry& repoRegistry){
    ticket_repos = std::dynamic_pointer_cast<TicketRepository>(repoRegistry.ticket_repos);
    showtime_repos = std::dynamic_pointer_cast<ShowTimeRepository>(repoRegistry.show_time_repos);
    movie_repos = std::dynamic_pointer_cast<MovieRepository>(repoRegistry.movie_repos);
    ss_repos = std::dynamic_pointer_cast<SeatScheduleRepository>(repoRegistry.seat_schedule_repos);
    seat_repos = std::dynamic_pointer_cast<SeatRepository>(repoRegistry.seat_repos);

    if (!ticket_repos || !showtime_repos || !movie_repos || !ss_repos || !seat_repos) {
        throw std::runtime_error("Failed to initialize TicketService: Repositories not found");
        Logger::getInstance()->log("Failed to initialize TicketService: Repositories not found");
    }
}

 void TicketService::bookTicket(User user) {

    vector<Movie> movies = movie_repos->findAll().data;
    if (movies.empty()) {
        cout << "Khong co phim trong CSDL \n";
        return;
    }
    printMovieVector(movies);
    int stt_phim;
    cout << "Nhap stt phim muon dat: \n";
    std::cin >> stt_phim;
    while(stt_phim < 1 || stt_phim > movies.size()){
        cout << "Stt khong hop le! Nhap lai stt: ";
        std::cin >> stt_phim;
    }
    // in chi tiet phim
    cout << "--------------------------------\n";
    cout << "Phim ban chon: " << movies[stt_phim - 1].getMovieTitle() << "\n";
    cout << "The loai: " << movies[stt_phim - 1].getMovieGenre() << "\n";
    cout << "Mo ta: " << movies[stt_phim - 1].getMovieDescription() << "\n";
    cout << "Thoi gian: " << movies[stt_phim - 1].getMovieDuration() << " phut\n";
    cout << "Danh gia: " << movies[stt_phim - 1].getMovieRating() << "\n";
    cout << "Gia ve: " << NumberFormatter::formatNumber(movies[stt_phim - 1].getPrice(), CultureInfo::get()) << CultureInfo::get().currency << "\n\n";

    Result<vector<ShowTime>> result_st = showtime_repos->findShowTimeByMovieId(movies[stt_phim - 1].getMovieId());
    
    if (!result_st.success || result_st.data.empty()) {
        cout << "Khong tim thay xuat chieu cho phim nay.\n";
        return;
    }

    cout << "Cac xuat chieu co cua phim:\n";
    for (int i = 0; i < result_st.data.size(); i++) {
        std::cout << "Stt: " << i + 1 << std::endl;
        std::cout << "Room ID: " << result_st.data[i].getRoomId() << std::endl;
        std::cout << "Theater ID: " << result_st.data[i].getTheaterId() << std::endl;
        std::cout << "Show Time: " << result_st.data[i].getShowTime() <<" "  << CultureInfo::get().time_zone << std::endl;
        std::cout << "--------------------------------\n";
    }
    int stt_xuat_chieu;
    cout << "\n";
    cout << "Chon xuat chieu muon dat ve: ";
    std::cin >> stt_xuat_chieu;
    while(stt_xuat_chieu < 1 || stt_xuat_chieu > result_st.data.size()){
        cout << "Stt khong hop le! Nhap lai stt: "; 
        std::cin >> stt_xuat_chieu;
    }
    cout << "--------------------------------\n";


    
    Result<vector<SeatSchedule>> ss_result = ss_repos->findAvailableSeats(
        result_st.data[stt_xuat_chieu - 1].getRoomId(),
        result_st.data[stt_xuat_chieu - 1].getTheaterId(),
        result_st.data[stt_xuat_chieu - 1].getShowTime()
    );

    if (!ss_result.success || ss_result.data.empty()) {
        cout << "Khong con ghe trong.\n";
        return;
    }

    cout << "Cac ghe con trong: ";
    for (const auto& ss : ss_result.data) {
        cout << ss.getSeatNumber() << " ";
    }

    std::cin.ignore();
    string seat_number;
    cout << "\nChon so ghe theo list tren: ";
    getline(std::cin, seat_number);

    
    Ticket cur_ticket = Ticket(
        0,
        user.getUserId(),
        result_st.data[stt_xuat_chieu - 1].getRoomId(),
        result_st.data[stt_xuat_chieu - 1].getTheaterId(),
        seat_number,
        result_st.data[stt_xuat_chieu - 1].getShowTime(),
        movies[stt_phim - 1].getPrice(),
        "",
        false
    );

    TicketContext ctx;
    ctx.ticket = cur_ticket;
    ctx.user = user;
    ctx.seat = seat_repos->findById(
        result_st.data[stt_xuat_chieu - 1].getRoomId(),
        result_st.data[stt_xuat_chieu - 1].getTheaterId(),
        seat_number
    ).data;
    PricingContext pricingContext;
    pricingContext.loadStrategiesFromDatabase();
    double finalPrice = pricingContext.calculatePrice(ctx);
    cur_ticket.setPrice(finalPrice);

    
    
    Result<int> insert_result = this->ticket_repos->create(cur_ticket);
    if (!insert_result.success) {
        cout << "Dat ve that bai: " << insert_result.error_message << "\n";
        return;
    }
    
    int ticket_id = insert_result.data;
    SeatSchedule seat_to_update (
        ss_result.data[stt_xuat_chieu - 1].getRoomId(),
        ss_result.data[stt_xuat_chieu - 1].getTheaterId(),
        ss_result.data[stt_xuat_chieu - 1].getSeatNumber(),
        ss_result.data[stt_xuat_chieu - 1].getShowTime(),
        ticket_id
    );
    
    
    Result<bool> update_result = ss_repos->update(seat_to_update);
    if (!update_result.success) {
        cout << "Cap nhat SeatSchedule that bai: " << update_result.error_message << "\n";
        return;
    }
    
    cout << "Dat ve thanh cong! Ma ve: " << ticket_id << "\n";
    cout  << "\nGia ve cua ban: " << NumberFormatter::formatNumber(cur_ticket.getPrice(), CultureInfo::get()) << " " << CultureInfo::get().currency << "\n";
}


void TicketService::viewUserTicket(User user){
    Result<vector<Ticket>> result = ticket_repos->findByUserId(user.getUserId());
    if(!result.success){
        cout << result.error_message << "\n";
        return;
    }
    const vector<Ticket>& tickets = result.data;
    if(tickets.empty()){
        cout << "Khong co ve cua ban trong CSDL \n";
        return;
    }
    printTicketTable(tickets);
}