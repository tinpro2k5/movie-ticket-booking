#include "../../include/services/TicketService.h"

 TicketService::TicketService(RepositoryRegistry& repoRegistry){
    ticket_repos = std::dynamic_pointer_cast<TicketRepository>(repoRegistry.ticket_repos);
    showtime_repos = std::dynamic_pointer_cast<ShowTimeRepository>(repoRegistry.show_time_repos);
    movie_repos = std::dynamic_pointer_cast<MovieRepository>(repoRegistry.movie_repos);
    ss_repos = std::dynamic_pointer_cast<SeatScheduleRepository>(repoRegistry.seat_schedule_repos);
    seat_repos = std::dynamic_pointer_cast<SeatRepository>(repoRegistry.seat_repos);
    theater_repos = std::dynamic_pointer_cast<MovieTheaterRepository>(repoRegistry.movie_theater_repos);

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

void TicketService::bookTicketUI(User user, wxWindow* parent) {
    // 1. Chọn phim
    Result<std::vector<Movie>> movieResult = movie_repos->findAll();
    if (!movieResult.success || movieResult.data.empty()) {
        wxMessageBox("No movies in database.", "Error", wxOK | wxICON_ERROR, parent);
        return;
    }
    wxArrayString movieTitles;
    for (const auto& m : movieResult.data)
        movieTitles.Add(wxString::FromUTF8(m.getMovieTitle().c_str()));

    wxSingleChoiceDialog movieDlg(parent, "Select a movie:", "Book Ticket", movieTitles);
    if (movieDlg.ShowModal() != wxID_OK) return;
    int movieIdx = movieDlg.GetSelection();
    const Movie& selectedMovie = movieResult.data[movieIdx];

    // 2. Chọn suất chiếu
    Result<std::vector<ShowTime>> stResult = showtime_repos->findShowTimeByMovieId(selectedMovie.getMovieId());
    if (!stResult.success || stResult.data.empty()) {
        wxMessageBox("No showtimes for this movie.", "Error", wxOK | wxICON_ERROR, parent);
        return;
    }
    wxArrayString showtimeChoices;
    std::vector<std::string> showtimeData;

    // Lấy danh sách rạp
    Result<std::vector<MovieTheater>> theatersResult = theater_repos->findAll();

    for (const auto& st : stResult.data) {
        // Tìm tên rạp theo theaterId
        std::string theaterName = "";
        if (theatersResult.success) {
            for (const auto& theater : theatersResult.data) {
                if (theater.getTheaterId() == st.getTheaterId()) {
                    theaterName = theater.getTheaterName();
                    break;
                }
            }
        }
        wxString label = wxString::Format("Theater: %s | Room %d | %s %s",
            wxString::FromUTF8(theaterName.c_str()).wx_str(),
            st.getRoomId(),
            wxString::FromUTF8(st.getShowTime().c_str()).wx_str(),
            wxString::FromUTF8(CultureInfo::get().time_zone.c_str()).wx_str()
        );
        showtimeChoices.Add(label);
        showtimeData.push_back(
            std::to_string(st.getRoomId()) + "|" +
            std::to_string(st.getTheaterId()) + "|" +
            st.getShowTime()
        );
    }
    wxSingleChoiceDialog stDlg(parent, "Select a showtime:", "Book Ticket", showtimeChoices);
    if (stDlg.ShowModal() != wxID_OK) return;
    int stIdx = stDlg.GetSelection();
    wxArrayString stParts = wxSplit(wxString::FromUTF8(showtimeData[stIdx].c_str()), '|');
    int roomId = wxAtoi(stParts[0]);
    int theaterId = wxAtoi(stParts[1]);
    std::string showTime = stParts[2].ToStdString();

    // 3. Chọn ghế
    Result<std::vector<SeatSchedule>> ssResult = ss_repos->findAvailableSeats(roomId, theaterId, showTime);
    if (!ssResult.success || ssResult.data.empty()) {
        wxMessageBox("No available seats.", "Error", wxOK | wxICON_ERROR, parent);
        return;
    }
    wxArrayString seatChoices;
    for (const auto& ss : ssResult.data)
        seatChoices.Add(wxString::FromUTF8(ss.getSeatNumber().c_str()));
    wxSingleChoiceDialog seatDlg(parent, "Select a seat:", "Book Ticket", seatChoices);
    if (seatDlg.ShowModal() != wxID_OK) return;
    wxString seatNumber = seatDlg.GetStringSelection();

    // 4. Tính giá vé
    Ticket cur_ticket(0, user.getUserId(), roomId, theaterId, seatNumber.ToStdString(), showTime, selectedMovie.getPrice(), "", false);
    TicketContext ctx;
    ctx.ticket = cur_ticket;
    ctx.user = user;
    ctx.seat = seat_repos->findById(roomId, theaterId, seatNumber.ToStdString()).data;
    PricingContext pricingContext;
    pricingContext.loadStrategiesFromDatabase();
    double finalPrice = pricingContext.calculatePrice(ctx);
    cur_ticket.setPrice(finalPrice);

    // 5. Xác nhận đặt vé
    wxString confirmMsg = wxString::Format(
        "Movie: %s\nShowtime: %s\nSeat: %s\nPrice: %.0f %s\n\nDo you want to book this ticket?",
        wxString::FromUTF8(selectedMovie.getMovieTitle().c_str()).wx_str(),
        wxString::FromUTF8(showTime.c_str()).wx_str(),
        seatNumber.wx_str(),
        finalPrice,
        wxString::FromUTF8(CultureInfo::get().currency.c_str()).wx_str()
    );
    if (wxMessageBox(confirmMsg, "Confirm Booking", wxYES_NO | wxICON_QUESTION, parent) != wxYES)
        return;

    // 6. Lưu vé và cập nhật ghế
    Result<int> insert_result = ticket_repos->create(cur_ticket);
    if (!insert_result.success) {
        wxMessageBox(wxString::FromUTF8(insert_result.error_message.c_str()), "Booking failed", wxOK | wxICON_ERROR, parent);
        return;
    }
    int ticket_id = insert_result.data;
    SeatSchedule seat_to_update(roomId, theaterId, seatNumber.ToStdString(), showTime, ticket_id);
    Result<bool> update_result = ss_repos->update(seat_to_update);
    if (!update_result.success) {
        wxMessageBox(wxString::FromUTF8(update_result.error_message.c_str()), "Seat update failed", wxOK | wxICON_ERROR, parent);
        return;
    }

    wxString msg = "Booking successful!\nYour ticket ID: " + wxString::Format("%d", ticket_id)
        + "\nPrice: " + wxString::Format("%.0f", finalPrice) + " " + wxString::FromUTF8(CultureInfo::get().currency.c_str());
    wxMessageBox(msg, "Success", wxOK | wxICON_INFORMATION, parent);
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

void TicketService::viewUserTicketUI(User user, wxWindow* parent) {
    Result<std::vector<Ticket>> result = ticket_repos->findByUserId(user.getUserId());
    if (!result.success) {
        wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, parent);
        return;
    }
    const std::vector<Ticket>& tickets = result.data;
    if (tickets.empty()) {
        wxMessageBox("You have no tickets in the database.", "Info", wxOK | wxICON_INFORMATION, parent);
        return;
    }

    wxDialog dlg(parent, wxID_ANY, "Your Tickets", wxDefaultPosition, wxSize(1000, 500));
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxListCtrl* listCtrl = new wxListCtrl(&dlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    listCtrl->InsertColumn(0, "Ticket ID", wxLIST_FORMAT_CENTER, 80);
    listCtrl->InsertColumn(1, "Room", wxLIST_FORMAT_CENTER, 60);
    listCtrl->InsertColumn(2, "Theater", wxLIST_FORMAT_CENTER, 70);
    listCtrl->InsertColumn(3, "Seat", wxLIST_FORMAT_CENTER, 70);
    listCtrl->InsertColumn(4, "Showtime", wxLIST_FORMAT_LEFT, 180);
    listCtrl->InsertColumn(5, "Booking Time", wxLIST_FORMAT_LEFT, 180);
    listCtrl->InsertColumn(6, "Price", wxLIST_FORMAT_RIGHT, 100);
    listCtrl->InsertColumn(7, "Paid", wxLIST_FORMAT_CENTER, 80);

    for (size_t i = 0; i < tickets.size(); ++i) {
        const Ticket& t = tickets[i];
        listCtrl->InsertItem(i, wxString::Format("%d", t.getTicketId()));
        listCtrl->SetItem(i, 1, wxString::Format("%d", t.getRoomId()));
        listCtrl->SetItem(i, 2, wxString::Format("%d", t.getTheaterId()));
        listCtrl->SetItem(i, 3, wxString::FromUTF8(t.getSeatNumber().c_str()));
        listCtrl->SetItem(i, 4, wxString::FromUTF8(t.getShowTime().c_str()));
        // Booking Time
        listCtrl->SetItem(i, 5, wxString::FromUTF8(t.getBookingTime().c_str()));
        // Price
        wxString priceStr = wxString::Format("%.0f %s", t.getPrice(), wxString::FromUTF8(CultureInfo::get().currency.c_str()).wx_str());
        listCtrl->SetItem(i, 6, priceStr);
        // Paid
        wxString paidStr = t.isPaid() ? "Done" : "Unpaid"; 
        listCtrl->SetItem(i, 7, paidStr);
        // Optional: màu cho unpaid
        if (!t.isPaid()) listCtrl->SetItemBackgroundColour(i, wxColour(255, 240, 240));
    }

    mainSizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);

    wxButton* btnClose = new wxButton(&dlg, wxID_CANCEL, "Close");
    mainSizer->Add(btnClose, 0, wxALIGN_CENTER | wxBOTTOM, 10);

    dlg.SetSizerAndFit(mainSizer);

    btnClose->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        dlg.EndModal(wxID_CANCEL);
    });

    dlg.ShowModal();
}