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

    cout << "Danh sach phim: \n";
    for (int i = 0; i < movies.size(); i++) {
        std::cout  << "Stt: " << i + 1 << std::endl;      
        std::cout << "Movie Title: " << movies[i].getMovieTitle() << std::endl;
        std::cout << "Movie Genre: " << movies[i].getMovieGenre() << std::endl;
        std::cout << "Movie Duration: " << movies[i].getMovieDuration() << std::endl;

    }

    int stt_phim;
    //Nhap phim muon dat
    cout << "Nhap stt phim muon dat: \n";
    std::cin >> stt_phim;
    while(stt_phim < 1 || stt_phim > movies.size()){
        cout << "Stt khong hop le! Nhap lai stt > 1 va < " << movies.size() << "\n";
        std::cin >> stt_phim;
    }

    cout << "--------------------------------\n";
    cout << "Movie Title: " << movies[stt_phim - 1].getMovieTitle() << std::endl;
    cout << "Movie Genre: " << movies[stt_phim - 1].getMovieGenre() << std::endl;
    cout << "Movie Duration: " << movies[stt_phim - 1].getMovieDuration() << std::endl;
    cout << "Movie Description: " << movies[stt_phim - 1].getMovieDescription() << std::endl;
    cout << "Movie Rating: " << movies[stt_phim - 1].getMovieRating() << std::endl;
    cout << "Movie Price: " << movies[stt_phim - 1].getPrice() << std::endl;
    cout << "--------------------------------\n";


    
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
        std::cout << "Show Time: " << result_st.data[i].getShowTime() << std::endl;
    }
    int stt_xuat_chieu;
    cout << "--------------------------------\n";
    cout << "Chon xuat chieu muon dat ve: \n";
    std::cin >> stt_xuat_chieu;
    while(stt_xuat_chieu < 1 || stt_xuat_chieu > result_st.data.size()){
        cout << "Stt khong hop le! Nhap lai stt > 1 va < " << result_st.data.size() << "\n";
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

    cout  << "\nGia ve cua ban: " << finalPrice << std::endl;


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
        cur_ticket.getTicketId()
    );


    Result<bool> update_result = ss_repos->update(seat_to_update);
    if (!update_result.success) {
        cout << "Cap nhat SeatSchedule that bai: " << update_result.error_message << "\n";
        return;
    }

    cout << "Dat ve thanh cong! Ma ve: " << ticket_id << "\n";
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
    cout << "All tickets you have bought.\n";
    for (int i = 0; i < tickets.size(); i++) {
        cout << "Ticket ID: " << result.data[i].getTicketId() << endl;
        cout << "User ID: " << result.data[i].getUserId() << endl;
        cout << "Room ID: " << result.data[i].getRoomId() << endl;
        cout << "Theater ID: " << result.data[i].getTheaterId() << endl;
        cout << "Seat Number: " << result.data[i].getSeatNumber() << endl;
        cout << "Show Time: " << result.data[i].getShowTime() << endl;
        cout << "Price: " << result.data[i].getPrice() << endl;
        cout << "Booking Time: " << result.data[i].getBookingTime() << endl;
        cout << "Is Paid: " << (result.data[i].isPaid() ? "Yes" : "No") << endl;
    }
}