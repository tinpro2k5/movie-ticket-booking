#include "../../include/services/ShowTimeService.h"

ShowTimeService::ShowTimeService(RepositoryRegistry& repoRegistry) {
    show_time_repos = std::dynamic_pointer_cast<ShowTimeRepository>(repoRegistry.show_time_repos);
    seat_schedule_repos = std::dynamic_pointer_cast<SeatScheduleRepository>(repoRegistry.seat_schedule_repos);
    user_repos = std::dynamic_pointer_cast<UserRepository>(repoRegistry.user_repos);
    ticket_repos = std::dynamic_pointer_cast<TicketRepository>(repoRegistry.ticket_repos);
    room_repos = std::dynamic_pointer_cast<RoomRepository>(repoRegistry.room_repos);
    movie_theater_repos = std::dynamic_pointer_cast<MovieTheaterRepository>(repoRegistry.movie_theater_repos);
    movie_repos = std::dynamic_pointer_cast<MovieRepository>(repoRegistry.movie_repos);
    if (!show_time_repos || !seat_schedule_repos || !user_repos || !ticket_repos || !room_repos || !movie_theater_repos || !movie_repos) {
        throw std::runtime_error("Failed to initialize ShowTimeService: Repositories not found");
    }
}
void ShowTimeService::manageShowTime(User user) {
    std::cout << "===== QUẢN LÝ LỊCH CHIẾU =====\n";
    std::cout << "1. Thêm lịch chiếu\n";
    std::cout << "2. Xóa lịch chiếu\n";
    std::cout << "3. Xem lịch chiếu\n";
    std::cout << "0. Thoát\n";
    std::cout << "=============================\n";
    int choice;
    cout << "Nhập lựa chọn của bạn: ";
    std::cin >> choice;
    switch (choice) {
        case 1: {
            ShowTime showtime;
            std::cin.ignore();
            std::cout << "Nhập ID phim: ";
            int movie_id;
            std::cin >> movie_id;
            showtime.setMovieId(movie_id);
            std::cout << "Nhập ID rạp: ";
            int theater_id;
            std::cin >> theater_id;
            showtime.setTheaterId(theater_id);
            int room_id;
            std::cout << "Nhập ID phòng: ";
            std::cin >> room_id;
            showtime.setRoomId(room_id);
            std::cin.ignore();
            std::cout << "Nhập thời gian chiếu (YYYY-MM-DD HH:MM:SS): ";
            std::string time;
            std::getline(std::cin, time);
            showtime.setShowTime(time);
            Result<int> result = show_time_repos->create(showtime);
            SeatSchedule seat_schedule(showtime.getRoomId(), showtime.getTheaterId(), "", showtime.getShowTime(), 0);
            vector<string> seat_numbers = {
                "A1", "A2", "A3", "A4", "A5",
                "B1", "B2", "B3", "B4", "B5",
                "C1", "C2", "C3", "C4", "C5"
            };
            for(int i = 0; i < 15; i++){
                seat_schedule.setSeatNumber(seat_numbers[i]);
                Result<int> insert_result = seat_schedule_repos->create(seat_schedule);
                if (!insert_result.success) {
                    std::cout << "Thêm ghế thất bại: " << insert_result.error_message << "\n";
                    return;
                }
            }
            if (!result.success) {
                std::cout << result.error_message << "\n";
                return;
            } else {
                std::cout << "Thêm lịch chiếu thành công \n";
            }
            break;
        }
        case 2: {
            std::cout << "====Xóa lịch chiếu====\n";
            int room_id;
            std::cout << "Nhập ID phòng: ";
            std::cin >> room_id;
            int theater_id;
            std::cout << "Nhập ID rạp: ";
            std::cin >> theater_id;
            std::cin.ignore();
            std::cout << "Nhập thời gian chiếu (YYYY-MM-DD HH:MM:SS): ";
            std::string time;
            std::getline(std::cin, time);
            ShowTime showtime;
            showtime.setRoomId(room_id);
            showtime.setTheaterId(theater_id);
            showtime.setShowTime(time);
            auto ticket_result = ticket_repos->findHavingShowTime(showtime);
            if (!ticket_result.success) {
                std::cout << ticket_result.error_message << "\n";
            }
            else if (ticket_result.data.size() > 0) {
                for (const auto& ticket : ticket_result.data) {
                User user = user_repos->findUserById(ticket.getUserId()).data[0];

                std::string message;
                message += "Vé ID: " + std::to_string(ticket.getTicketId()) + "\n";
                message += "Rạp: " + std::to_string(showtime.getTheaterId()) + "\n";
                message += "Phòng: " + std::to_string(showtime.getRoomId()) + "\n";
                message += "Thời gian: " + showtime.getShowTime() + "\n";
                message += "Ghế: " + ticket.getSeatNumber() + "\n";
                message += "Xin lỗi vì sự bất tiện này.\n";

                EmailService::sendShowTimeCancelation(user.getEmail(), message);
                
                std::cout << "Đã gửi thông báo hủy lịch chiếu đến người dùng: " << user.getEmail() << "\n";
                }
            } 
            else {
                std::cout << "Không có vé nào cho lịch chiếu này.\n";
            }

            Result<bool> result = show_time_repos->remove(showtime);
            if (!result.success) {
                std::cout << result.error_message << "\n";
                return;
            } else {
                std::cout << "Xóa lịch chiếu thành công \n";
            }

            break;
        }
        case 3: {
            cout << "====Xem lịch chiếu====\n";
            cout << "1. Theo ID phim\n";
            cout << "2. Theo ID rạp\n";
            cout << "0. Thoát\n";
            cout << "=====================\n";
            int choice;
            cout << "Nhập lựa chọn của bạn: ";
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    Result<vector<Movie>> list_movie = movie_repos->findAll();
                    if (!list_movie.success) {
                        std::cout << list_movie.error_message << "\n";
                        return;
                    }
                    printMoviesTable(list_movie.data);
                    std::cout << "Nhập ID phim: ";
                    int movie_id;
                    std::cin >> movie_id;
                    Result<vector<ShowTime>> result = show_time_repos->findShowTimeByMovieId(movie_id);
                    if (!result.success) {
                        std::cout << result.error_message << "\n";
                        return;
                    }
                    printShowtimeTable(result.data);
                    break;
                }
                case 2: {
                    Result<vector<MovieTheater>> list_theater = movie_theater_repos->findAll();
                    if (!list_theater.success) {
                        std::cout << list_theater.error_message << "\n";
                        return;
                    }
                    printTheaterTable(list_theater.data);
                    std::cout << "Nhập ID rạp: ";
                    int theater_id;
                    std::cin >> theater_id;
                    Result<vector<ShowTime>> result = show_time_repos->findShowTimeByTheaterId(theater_id);
                    if (!result.success) {
                        std::cout << result.error_message << "\n";
                        return;
                    }
                    printShowtimeTable(result.data);
                    break;
                }
                case 0:
                    return;
            }
            break;
        }
        default:
            return;
    }
}

void ShowTimeService::manageShowTimeUI(wxWindow* parent, User user) {
    wxDialog dlg(parent, wxID_ANY, "Showtime Management", wxDefaultPosition, wxSize(500, 400));
    dlg.SetBackgroundColour(wxColour(245, 247, 250));
    dlg.Centre();

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Title
    wxStaticText* title = new wxStaticText(&dlg, wxID_ANY, "🎬 Showtime Management");
    wxFont titleFont(wxFontInfo(22).Bold().FaceName("Arial"));
    title->SetFont(titleFont);
    title->SetForegroundColour(wxColour(41, 128, 185));
    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 22);

    // Subtitle
    wxStaticText* subtitle = new wxStaticText(&dlg, wxID_ANY, "Choose an action below:");
    wxFont subFont(wxFontInfo(13).Italic().FaceName("Arial"));
    subtitle->SetFont(subFont);
    subtitle->SetForegroundColour(wxColour(52, 152, 219));
    vbox->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 18);

    // Buttons
    wxButton* btnAdd    = new wxButton(&dlg, wxID_ANY, "Add Showtime");
    wxButton* btnDelete = new wxButton(&dlg, wxID_ANY, "Delete Showtime");
    wxButton* btnView   = new wxButton(&dlg, wxID_ANY, "View Showtimes");
    wxButton* btnExit   = new wxButton(&dlg, wxID_EXIT, "Exit");

    wxFont btnFont(wxFontInfo(15).Bold().FaceName("Arial"));
    const int BTN_HEIGHT = 48;
    const int BTN_WIDTH = 320;

    auto styleBtn = [&](wxButton* btn, wxColour bg, wxColour fg) {
        btn->SetFont(btnFont);
        btn->SetBackgroundColour(bg);
        btn->SetForegroundColour(fg);
        btn->SetMinSize(wxSize(BTN_WIDTH, BTN_HEIGHT));
        btn->SetWindowStyleFlag(wxBORDER_NONE);
    };

    styleBtn(btnAdd,    wxColour(52, 152, 219),  *wxWHITE); // Blue
    styleBtn(btnDelete, wxColour(231, 76, 60),   *wxWHITE); // Red
    styleBtn(btnView,   wxColour(46, 204, 113),  *wxWHITE); // Green
    styleBtn(btnExit,   wxColour(149, 165, 166), *wxWHITE); // Gray

    vbox->Add(btnAdd,    0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(btnDelete, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnView,   0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnExit,   0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 18);

    // Footer
    wxStaticText* footer = new wxStaticText(&dlg, wxID_ANY, "© 2025 Movie Ticket Booking");
    footer->SetForegroundColour(wxColour(160, 160, 160));
    wxFont footerFont(wxFontInfo(10).FaceName("Arial"));
    footer->SetFont(footerFont);
    vbox->Add(footer, 0, wxALIGN_CENTER | wxBOTTOM, 8);

    dlg.SetSizerAndFit(vbox);

    // Add Showtime
    btnAdd->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        Result<std::vector<Movie>> movies = movie_repos->findAll();
        Result<std::vector<MovieTheater>> theaters = movie_theater_repos->findAll();
        Result<std::vector<Room>> rooms = room_repos->findAll();
        if (!movies.success || movies.data.empty() || !theaters.success || theaters.data.empty() || !rooms.success || rooms.data.empty()) {
            wxMessageBox("Please make sure there are movies, theaters, and rooms available!", "Error", wxOK | wxICON_ERROR, &dlg);
            return;
        }

        wxDialog addDlg(&dlg, wxID_ANY, "Add Showtime", wxDefaultPosition, wxSize(400, 350));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
        wxFlexGridSizer* grid = new wxFlexGridSizer(2, 10, 10);
        grid->AddGrowableCol(1, 1);

        // Movie
        wxStaticText* lblMovie = new wxStaticText(&addDlg, wxID_ANY, "Movie:");
        wxArrayString movieChoices;
        std::vector<int> movieIds;
        for (const auto& m : movies.data) {
            movieChoices.Add(wxString::Format("%d - %s", m.getMovieId(), m.getMovieTitle()));
            movieIds.push_back(m.getMovieId());
        }
        wxChoice* choiceMovie = new wxChoice(&addDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, movieChoices);
        choiceMovie->SetSelection(0);

        // Theater
        wxStaticText* lblTheater = new wxStaticText(&addDlg, wxID_ANY, "Theater:");
        wxArrayString theaterChoices;
        std::vector<int> theaterIds;
        for (const auto& t : theaters.data) {
            theaterChoices.Add(wxString::Format("%d - %s", t.getTheaterId(), t.getTheaterName()));
            theaterIds.push_back(t.getTheaterId());
        }
        wxChoice* choiceTheater = new wxChoice(&addDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, theaterChoices);
        choiceTheater->SetSelection(0);

        // Room (filtered by theater)
        wxStaticText* lblRoom = new wxStaticText(&addDlg, wxID_ANY, "Room:");
        wxArrayString roomChoices;
        std::vector<int> roomIds;

        // Hàm cập nhật danh sách room theo theater đã chọn
        auto updateRoomChoices = [&](int theaterIdx) {
            roomChoices.Clear();
            roomIds.clear();
            int theaterId = theaterIds[theaterIdx];
            for (const auto& r : rooms.data) {
                if (r.getTheaterId() == theaterId) {
                    roomChoices.Add(wxString::Format("%d - %s", r.getRoomId(), r.getRoomName()));
                    roomIds.push_back(r.getRoomId());
                }
            }
        };

        updateRoomChoices(0); // Ban đầu lấy theo theater đầu tiên
        wxChoice* choiceRoom = new wxChoice(&addDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, roomChoices);
        choiceRoom->SetSelection(0);

        // Khi chọn theater, cập nhật lại room
        choiceTheater->Bind(wxEVT_CHOICE, [&](wxCommandEvent& evt) {
            int sel = choiceTheater->GetSelection();
            updateRoomChoices(sel);
            choiceRoom->Clear();
            choiceRoom->Append(roomChoices);
            if (!roomChoices.IsEmpty())
                choiceRoom->SetSelection(0);
        });

        // Time
        wxStaticText* lblTime = new wxStaticText(&addDlg, wxID_ANY, "Showtime (YYYY-MM-DD HH:MM:SS):");
        wxTextCtrl* txtTime = new wxTextCtrl(&addDlg, wxID_ANY);

        grid->Add(lblMovie, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(choiceMovie, 1, wxEXPAND);
        grid->Add(lblTheater, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(choiceTheater, 1, wxEXPAND);
        grid->Add(lblRoom, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(choiceRoom, 1, wxEXPAND);
        grid->Add(lblTime, 0, wxALIGN_CENTER_VERTICAL);
        grid->Add(txtTime, 1, wxEXPAND);

        mainSizer->Add(grid, 1, wxALL | wxEXPAND, 15);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnOK = new wxButton(&addDlg, wxID_OK, "Add");
        wxButton* btnCancel = new wxButton(&addDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnOK, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);
        mainSizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        addDlg.SetSizerAndFit(mainSizer);

        if (addDlg.ShowModal() == wxID_OK) {
            int movieSel = choiceMovie->GetSelection();
            int theaterSel = choiceTheater->GetSelection();
            int roomSel = choiceRoom->GetSelection();
            std::string time = txtTime->GetValue().ToStdString();

            if (movieSel < 0 || theaterSel < 0 || roomSel < 0 || time.empty()) {
                wxMessageBox("Please enter all required information!", "Input Error", wxOK | wxICON_ERROR, &addDlg);
                return;
            }

            ShowTime showtime;
            showtime.setMovieId(movieIds[movieSel]);
            showtime.setTheaterId(theaterIds[theaterSel]);
            showtime.setRoomId(roomIds[roomSel]);
            showtime.setShowTime(time);

            Result<int> result = show_time_repos->create(showtime);

            // Tạo seat schedule mẫu (15 ghế)
            SeatSchedule seat_schedule(showtime.getRoomId(), showtime.getTheaterId(), "", showtime.getShowTime(), 0);
            std::vector<std::string> seat_numbers = {
                "A1", "A2", "A3", "A4", "A5",
                "B1", "B2", "B3", "B4", "B5",
                "C1", "C2", "C3", "C4", "C5"
            };
            for (int i = 0; i < 15; i++) {
                seat_schedule.setSeatNumber(seat_numbers[i]);
                Result<int> insert_result = seat_schedule_repos->create(seat_schedule);
                if (!insert_result.success) {
                    wxMessageBox(wxString::Format("Failed to add seat: %s", insert_result.error_message), "Error", wxOK | wxICON_ERROR, &addDlg);
                    return;
                }
            }

            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &addDlg);
            } else {
                wxMessageBox("Showtime added successfully!", "Success", wxOK | wxICON_INFORMATION, &addDlg);
            }
        }
    });

    // Delete Showtime
    btnDelete->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        // Lấy danh sách theater
        Result<std::vector<MovieTheater>> theaters = movie_theater_repos->findAll();
        if (!theaters.success || theaters.data.empty()) {
            wxMessageBox("No theaters found!", "Info", wxOK | wxICON_INFORMATION, &dlg);
            return;
        }
        wxArrayString theaterChoices;
        std::vector<int> theaterIds;
        for (const auto& t : theaters.data) {
            theaterChoices.Add(wxString::Format("%d - %s", t.getTheaterId(), t.getTheaterName()));
            theaterIds.push_back(t.getTheaterId());
        }
        wxSingleChoiceDialog theaterDlg(&dlg, "Select a theater:", "Theaters", theaterChoices);
        if (theaterDlg.ShowModal() != wxID_OK) return;
        int theaterSel = theaterDlg.GetSelection();
        if (theaterSel < 0) return;
        int selectedTheaterId = theaterIds[theaterSel];

        // Lấy showtime của theater đã chọn
        Result<std::vector<ShowTime>> showtimes = show_time_repos->findShowTimeByTheaterId(selectedTheaterId);
        Result<std::vector<Movie>> movies = movie_repos->findAll();
        Result<std::vector<Room>> rooms = room_repos->findAll();

        if (!showtimes.success || showtimes.data.empty()) {
            wxMessageBox("No showtimes found for this theater!", "Info", wxOK | wxICON_INFORMATION, &dlg);
            return;
        }

        // Map id -> name/title
        std::map<int, std::string> movieMap, roomMap;
        for (const auto& m : movies.data) movieMap[m.getMovieId()] = m.getMovieTitle();
        for (const auto& r : rooms.data) roomMap[r.getRoomId()] = r.getRoomName();

        wxDialog delDlg(&dlg, wxID_ANY, "Delete Showtime", wxDefaultPosition, wxSize(700, 400));
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

        wxListCtrl* listCtrl = new wxListCtrl(&delDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
        listCtrl->InsertColumn(0, "Movie", wxLIST_FORMAT_LEFT, 180);
        listCtrl->InsertColumn(1, "Room", wxLIST_FORMAT_LEFT, 120);
        listCtrl->InsertColumn(2, "Time", wxLIST_FORMAT_LEFT, 250);

        // Hiển thị danh sách showtime của theater đã chọn
        long idx = 0;
        for (const auto& st : showtimes.data) {
            wxString movieName = wxString::FromUTF8(movieMap[st.getMovieId()].c_str());
            wxString roomName = wxString::FromUTF8(roomMap[st.getRoomId()].c_str());
            long item = listCtrl->InsertItem(idx, movieName);
            listCtrl->SetItem(item, 1, roomName);
            listCtrl->SetItem(item, 2, wxString::FromUTF8(st.getShowTime().c_str()));
            listCtrl->SetItemData(item, idx);
            ++idx;
        }

        sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);

        wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
        wxButton* btnDeleteSelected = new wxButton(&delDlg, wxID_OK, "Delete Selected");
        wxButton* btnCancel = new wxButton(&delDlg, wxID_CANCEL, "Cancel");
        btnSizer->Add(btnDeleteSelected, 0, wxRIGHT, 10);
        btnSizer->Add(btnCancel, 0);
        sizer->Add(btnSizer, 0, wxALIGN_CENTER | wxBOTTOM, 10);

        delDlg.SetSizerAndFit(sizer);

        btnDeleteSelected->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            long sel = listCtrl->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
            if (sel == -1) {
                wxMessageBox("Please select a showtime to delete.", "Warning", wxOK | wxICON_WARNING, &delDlg);
                return;
            }
            const ShowTime& st = showtimes.data[sel];

            // Xử lý gửi email nếu có vé
            auto ticket_result = ticket_repos->findHavingShowTime(st);
            if (!ticket_result.success) {
                wxMessageBox(wxString::FromUTF8(ticket_result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &delDlg);
            } else if (!ticket_result.data.empty()) {
                for (const auto& ticket : ticket_result.data) {
                    User user = user_repos->findUserById(ticket.getUserId()).data[0];
                    std::string message;
                    message += "Ticket ID: " + std::to_string(ticket.getTicketId()) + "\n";
                    message += "Theater: " + std::to_string(st.getTheaterId()) + "\n";
                    message += "Room: " + std::to_string(st.getRoomId()) + "\n";
                    message += "Time: " + st.getShowTime() + "\n";
                    message += "Seat: " + ticket.getSeatNumber() + "\n";
                    message += "Sorry for the inconvenience.\n";
                    EmailService::sendShowTimeCancelation(user.getEmail(), message);
                }
                wxMessageBox("Cancelation emails sent to users with tickets.", "Info", wxOK | wxICON_INFORMATION, &delDlg);
            } else {
                wxMessageBox("No tickets found for this showtime.", "Info", wxOK | wxICON_INFORMATION, &delDlg);
            }

            Result<bool> result = show_time_repos->remove(st);
            if (!result.success) {
                wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &delDlg);
            } else {
                wxMessageBox("Showtime deleted successfully!", "Success", wxOK | wxICON_INFORMATION, &delDlg);
                delDlg.EndModal(wxID_OK);
            }
        });

        btnCancel->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            delDlg.EndModal(wxID_CANCEL);
        });

        delDlg.ShowModal();
    });

    // View Showtimes
    btnView->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        wxDialog viewDlg(&dlg, wxID_ANY, "View Showtimes", wxDefaultPosition, wxSize(600, 400));
        wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

        wxButton* btnByMovie = new wxButton(&viewDlg, wxID_ANY, "By Movie");
        wxButton* btnByTheater = new wxButton(&viewDlg, wxID_ANY, "By Theater");
        wxButton* btnClose = new wxButton(&viewDlg, wxID_CANCEL, "Close");

        mainSizer->Add(btnByMovie, 0, wxEXPAND | wxALL, 10);
        mainSizer->Add(btnByTheater, 0, wxEXPAND | wxALL, 10);
        mainSizer->Add(btnClose, 0, wxEXPAND | wxALL, 10);

        viewDlg.SetSizerAndFit(mainSizer);

        btnByMovie->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            Result<std::vector<Movie>> list_movie = movie_repos->findAll();
            Result<std::vector<MovieTheater>> list_theater = movie_theater_repos->findAll();
            if (!list_movie.success || list_movie.data.empty()) {
                wxMessageBox("No movies found!", "Info", wxOK | wxICON_INFORMATION, &viewDlg);
                return;
            }
            wxArrayString movieChoices;
            std::vector<int> movieIds;
            for (const auto& m : list_movie.data) {
                movieChoices.Add(wxString::Format("%d - %s", m.getMovieId(), m.getMovieTitle()));
                movieIds.push_back(m.getMovieId());
            }
            wxSingleChoiceDialog movieDlg(&viewDlg, "Select a movie:", "Movies", movieChoices);
            if (movieDlg.ShowModal() == wxID_OK) {
                int sel = movieDlg.GetSelection();
                if (sel >= 0) {
                    Result<std::vector<ShowTime>> result = show_time_repos->findShowTimeByMovieId(movieIds[sel]);
                    if (!result.success) {
                        wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &viewDlg);
                        return;
                    }
                    // Map theaterId -> theaterName
                    std::map<int, std::string> theaterNameMap;
                    for (const auto& t : list_theater.data) {
                        theaterNameMap[t.getTheaterId()] = t.getTheaterName();
                    }
                    wxDialog listDlg(&viewDlg, wxID_ANY, "Showtimes", wxDefaultPosition, wxSize(600, 350));
                    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
                    wxListCtrl* listCtrl = new wxListCtrl(&listDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
                    listCtrl->InsertColumn(0, "Theater", wxLIST_FORMAT_LEFT, 180);
                    listCtrl->InsertColumn(1, "Room ID", wxLIST_FORMAT_LEFT, 100);
                    listCtrl->InsertColumn(2, "Time", wxLIST_FORMAT_LEFT, 250);
                    long idx = 0;
                    for (const auto& st : result.data) {
                        wxString theaterName = wxString::Format("%d", st.getTheaterId());
                        auto it = theaterNameMap.find(st.getTheaterId());
                        if (it != theaterNameMap.end()) {
                            theaterName = wxString::FromUTF8(it->second.c_str());
                        }
                        long item = listCtrl->InsertItem(idx, theaterName);
                        listCtrl->SetItem(item, 1, wxString::Format("%d", st.getRoomId()));
                        listCtrl->SetItem(item, 2, wxString::FromUTF8(st.getShowTime().c_str()));
                        ++idx;
                    }
                    sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);
                    wxButton* btnCloseList = new wxButton(&listDlg, wxID_ANY, "Close");
                    sizer->Add(btnCloseList, 0, wxALIGN_CENTER | wxBOTTOM, 10);
                    btnCloseList->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
                        listDlg.EndModal(wxID_OK);
                    });
                    listDlg.SetSizerAndFit(sizer);
                    listDlg.ShowModal();
                }
            }
        });

        btnByTheater->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            Result<std::vector<MovieTheater>> list_theater = movie_theater_repos->findAll();
            Result<std::vector<Movie>> list_movie = movie_repos->findAll();
            if (!list_theater.success || list_theater.data.empty()) {
                wxMessageBox("No theaters found!", "Info", wxOK | wxICON_INFORMATION, &viewDlg);
                return;
            }
            wxArrayString theaterChoices;
            std::vector<int> theaterIds;
            for (const auto& t : list_theater.data) {
                theaterChoices.Add(wxString::Format("%d - %s", t.getTheaterId(), t.getTheaterName()));
                theaterIds.push_back(t.getTheaterId());
            }
            wxSingleChoiceDialog theaterDlg(&viewDlg, "Select a theater:", "Theaters", theaterChoices);
            if (theaterDlg.ShowModal() == wxID_OK) {
                int sel = theaterDlg.GetSelection();
                if (sel >= 0) {
                    Result<std::vector<ShowTime>> result = show_time_repos->findShowTimeByTheaterId(theaterIds[sel]);
                    if (!result.success) {
                        wxMessageBox(wxString::FromUTF8(result.error_message.c_str()), "Error", wxOK | wxICON_ERROR, &viewDlg);
                        return;
                    }
                    // Map movieId -> movieTitle
                    std::map<int, std::string> movieNameMap;
                    for (const auto& m : list_movie.data) {
                        movieNameMap[m.getMovieId()] = m.getMovieTitle();
                    }
                    wxDialog listDlg(&viewDlg, wxID_ANY, "Showtimes", wxDefaultPosition, wxSize(600, 350));
                    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
                    wxListCtrl* listCtrl = new wxListCtrl(&listDlg, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT);
                    listCtrl->InsertColumn(0, "Movie", wxLIST_FORMAT_LEFT, 180);
                    listCtrl->InsertColumn(1, "Room ID", wxLIST_FORMAT_LEFT, 100);
                    listCtrl->InsertColumn(2, "Time", wxLIST_FORMAT_LEFT, 250);
                    long idx = 0;
                    for (const auto& st : result.data) {
                        wxString movieName = wxString::Format("%d", st.getMovieId());
                        auto it = movieNameMap.find(st.getMovieId());
                        if (it != movieNameMap.end()) {
                            movieName = wxString::FromUTF8(it->second.c_str());
                        }
                        long item = listCtrl->InsertItem(idx, movieName);
                        listCtrl->SetItem(item, 1, wxString::Format("%d", st.getRoomId()));
                        listCtrl->SetItem(item, 2, wxString::FromUTF8(st.getShowTime().c_str()));
                        ++idx;
                    }
                    sizer->Add(listCtrl, 1, wxEXPAND | wxALL, 10);
                    wxButton* btnCloseList = new wxButton(&listDlg, wxID_ANY, "Close");
                    sizer->Add(btnCloseList, 0, wxALIGN_CENTER | wxBOTTOM, 10);
                    btnCloseList->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
                        listDlg.EndModal(wxID_OK);
                    });
                    listDlg.SetSizerAndFit(sizer);
                    listDlg.ShowModal();
                }
            }
        });

        btnClose->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
            viewDlg.EndModal(wxID_CANCEL);
        });

        viewDlg.ShowModal();
    });

    btnExit->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        dlg.EndModal(wxID_EXIT);
    });

    dlg.ShowModal();
}