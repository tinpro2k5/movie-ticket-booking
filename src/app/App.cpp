/**
 * @file App.cpp
 * @brief Implements the App class, the main coordinator for the movie ticket booking application.
 *
 * This file contains the implementation of the App class methods, including application initialization,
 * user/admin menu handling, registration, login, and UI flows.
 *
 * Architecture overview:
 * - App acts as the entry point and orchestrator for all business logic and user interface flows.
 * - It manages the lifecycle of services, repositories, and command objects.
 * - Handles both console and GUI interactions for users and administrators.
 * - Integrates with utility classes such as Logger, DatabaseManager, and SessionManager.
 *
 * @see App.h
 */

#include "../../include/app/App.h"

/**
 * @brief App constructor. Initializes all core services, repositories, and command objects.
 * Sets up logging and culture information for the application.
 *
 * Architectural role: Entry point for dependency injection and system bootstrapping.
 */
App::App():
        repository_registry(),
        user_service(repository_registry),
        movie_service(repository_registry),
        ticket_service(repository_registry),
        show_time_service(repository_registry),
        room_service(repository_registry),
        theater_service(repository_registry),
        menu_invoker(),
        room_manage_commnand(&room_service),
        theater_manage_commnand(&theater_service),
        view_movie_command(&movie_service),
        filter_movie_command(&movie_service),
        book_ticket_command(&ticket_service),
        show_ticket_command(&ticket_service),
        movie_manage_command(&movie_service),
        show_time_manage_command(&show_time_service)
        
{
    CultureInfo::setCulture("vi-VN"); // Set default culture
    Logger::getInstance()->setLogFile(Logger::getInstance()->DEFAULT_LOG_FILE);
    Logger::getInstance()->log("App initialized", Logger::Level::INFO);
}

/**
 * @brief App destructor. Handles cleanup and resource release.
 *
 * Architectural role: Ensures proper shutdown and logging.
 */
App::~App() {
    Logger::getInstance()->log("App destroyed", Logger::Level::INFO);
    // Destructor
    // Clean up resources if needed
}

/**
 * @brief Main application loop. Handles authentication, menu routing, and session management.
 *
 * Architectural role: Central event loop, orchestrates user/admin flows and system state.
 * - Connects to the database and sets up schema.
 * - Handles login, registration, and menu navigation.
 */
int App::run() {
    ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
    cout << "------------------------------------------\n";
    Logger::getInstance()->log("Connecting to database: " + serverInfo.getHost(), Logger::Level::INFO); 
    cout << "------------------------------------------\n";
    DatabaseManager::getInstance()->connect(serverInfo);
    cout << "------------------------------------------\n";
    DatabaseManager::getInstance()->setupDatabase(INIT_DB_SCRIPT);
    cout << "------------------------------------------\n";
    int choice;
    while (true) {
        if (!SessionManager::isLoggedIn()){
            displayStartMenu();
            std::cin >> choice;
            switch (choice) {
                case 1: handleRegister(); break;
                case 2: handleLogin(); break;
                case 0: handleExit(); break;
                default:
                std::cout << "Lựa chọn không hợp lệ!\n";
            }
        }
        else if (SessionManager::isAdminUser()) {
            handleAdminMenu();  
        } 
        else if (!SessionManager::isAdminUser()) {
            handleUserMenu();
        }
        std::cout << "Nhấn phím bất kỳ để tiếp tục...\n";
        std::cin.ignore();
        std::cin.get();
        system("clear");
    }
}


/**
 * @brief Handles the admin menu in console mode.
 *
 * Architectural role: Provides admin with access to management commands via MenuInvoker.
 * - Sets up command pattern for admin actions.
 * - Handles session and logout.
 */
void App::handleAdminMenu() {
    User user = SessionManager::getCurrentUser();
    std::cout << "Xin chào " << user.getUsername() << "!\n";
    std::cout << "Bạn đã đăng nhập với quyền admin user.\n";
    std::cout << "------------------------------------------\n";

    menu_invoker.setCommand(1, &movie_manage_command);
    menu_invoker.setCommand(2, &show_time_manage_command);
    menu_invoker.setCommand(3, &theater_manage_commnand);
    menu_invoker.setCommand(4, &room_manage_commnand);
    int choice;
    do {
        menu_invoker.showMenuAdmin();
        std::cout << "Chọn chức năng: ";
        std::cin >> choice;
        if (choice != 0)
            menu_invoker.executeCommand(choice, user);
    } while (choice != 0);
    std::cout << "Đăng xuất thành công!\n";
    SessionManager::clear();
}

/**
 * @brief Handles the admin menu in GUI mode.
 *
 * Architectural role: Provides admin with access to management commands via MenuInvoker in a wxWidgets dialog.
 * - Binds UI buttons to command pattern actions.
 * - Handles session and logout.
 */
void App::handleAdminMenuUI(wxWindow* parent){
    User user = SessionManager::getCurrentUser();

    wxDialog dlg(parent, wxID_ANY, "Admin Menu", wxDefaultPosition, wxSize(350, 400));
    dlg.SetBackgroundColour(wxColour(245, 247, 250));
    dlg.Centre();

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Title
    wxString adminMsg = wxString::Format("Welcome, %s (Admin)", wxString::FromUTF8(user.getUsername().c_str()));
    wxStaticText* title = new wxStaticText(&dlg, wxID_ANY, adminMsg);
    wxFont titleFont(wxFontInfo(18).Bold().FaceName("Arial"));
    title->SetFont(titleFont);
    title->SetForegroundColour(wxColour(41, 128, 185));
    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 18);

    wxStaticText* subtitle = new wxStaticText(&dlg, wxID_ANY, "Please choose an action:");
    wxFont subFont(wxFontInfo(12).Italic().FaceName("Arial"));
    subtitle->SetFont(subFont);
    subtitle->SetForegroundColour(wxColour(52, 152, 219));
    vbox->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 12);

    // Các nút chức năng
    wxButton* btnMovies    = new wxButton(&dlg, wxID_ANY, "Manage Movies");
    wxButton* btnShowtimes = new wxButton(&dlg, wxID_ANY, "Manage Showtimes");
    wxButton* btnTheaters  = new wxButton(&dlg, wxID_ANY, "Manage Theaters");
    wxButton* btnRooms     = new wxButton(&dlg, wxID_ANY, "Manage Rooms");
    wxButton* btnLogout    = new wxButton(&dlg, wxID_EXIT, "Logout");

    wxFont btnFont(wxFontInfo(15).Bold().FaceName("Arial"));
    btnMovies->SetFont(btnFont);
    btnShowtimes->SetFont(btnFont);
    btnTheaters->SetFont(btnFont);
    btnRooms->SetFont(btnFont);
    btnLogout->SetFont(btnFont);

    btnMovies->SetBackgroundColour(wxColour(52, 152, 219));
    btnMovies->SetForegroundColour(*wxWHITE);
    btnShowtimes->SetBackgroundColour(wxColour(46, 204, 113));
    btnShowtimes->SetForegroundColour(*wxWHITE);
    btnTheaters->SetBackgroundColour(wxColour(241, 196, 15));
    btnTheaters->SetForegroundColour(*wxWHITE);
    btnRooms->SetBackgroundColour(wxColour(155, 89, 182));
    btnRooms->SetForegroundColour(*wxWHITE);
    btnLogout->SetBackgroundColour(wxColour(231, 76, 60));
    btnLogout->SetForegroundColour(*wxWHITE);

    btnMovies->SetMinSize(wxSize(260, 40));
    btnShowtimes->SetMinSize(wxSize(260, 40));
    btnTheaters->SetMinSize(wxSize(260, 40));
    btnRooms->SetMinSize(wxSize(260, 40));
    btnLogout->SetMinSize(wxSize(260, 40));

    btnMovies->SetWindowStyleFlag(wxBORDER_NONE);
    btnShowtimes->SetWindowStyleFlag(wxBORDER_NONE);
    btnTheaters->SetWindowStyleFlag(wxBORDER_NONE);
    btnRooms->SetWindowStyleFlag(wxBORDER_NONE);
    btnLogout->SetWindowStyleFlag(wxBORDER_NONE);

    vbox->Add(btnMovies,    0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(btnShowtimes, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnTheaters,  0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnRooms,     0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnLogout,    0, wxALIGN_CENTER | wxTOP, 18);

    // Footer
    wxStaticText* footer = new wxStaticText(&dlg, wxID_ANY, "© 2025 Movie Ticket Booking | Admin Panel");
    footer->SetForegroundColour(wxColour(160, 160, 160));
    wxFont footerFont(wxFontInfo(10).FaceName("Arial"));
    footer->SetFont(footerFont);
    vbox->Add(footer, 0, wxALIGN_CENTER | wxTOP, 12);

    dlg.SetSizerAndFit(vbox);

    // Gán command tương ứng với từng chức năng
    menu_invoker.setCommand(1, &movie_manage_command);
    menu_invoker.setCommand(2, &show_time_manage_command);
    menu_invoker.setCommand(3, &theater_manage_commnand);
    menu_invoker.setCommand(4, &room_manage_commnand);

    // Sự kiện cho từng nút
    btnMovies->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(1, user, parent);
    });
    btnShowtimes->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(2, user, parent);
    });
    btnTheaters->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(3, user, parent);
    });
    btnRooms->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(4, user, parent);
    });
    btnLogout->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        wxMessageBox("Logged out successfully!", "Notification", wxOK | wxICON_INFORMATION, &dlg);
        SessionManager::clear();
        dlg.EndModal(wxID_EXIT);
    });

    dlg.ShowModal();
}

/**
 * @brief Handles the user menu in console mode.
 *
 * Architectural role: Provides user with access to movie viewing, filtering, booking, and ticket management.
 * - Uses MenuInvoker to execute user commands.
 * - Handles session and logout.
 */
void App::handleUserMenu() {
    User user = SessionManager::getCurrentUser();
    std::cout << "Xin chào " << user.getUsername() << "!\n";
    std::cout << "Bạn đã đăng nhập với quyền user.\n";
    std::cout << "------------------------------------------\n";
    int movie_choice;
    menu_invoker.setCommand(1, &view_movie_command);
    menu_invoker.setCommand(2, &filter_movie_command);
    menu_invoker.setCommand(3, &book_ticket_command);
    menu_invoker.setCommand(4, &show_ticket_command);
    while (true) {
        menu_invoker.showMenuUser();
        std::cin >> movie_choice;
        if (movie_choice == 0) {
            break;
        }
        menu_invoker.executeCommand(movie_choice, user);
    }
    SessionManager::clear();
}

/**
 * @brief Handles the user menu in GUI mode.
 *
 * Architectural role: Provides user with access to movie viewing, filtering, booking, and ticket management in a wxWidgets dialog.
 * - Binds UI buttons to command pattern actions.
 * - Handles session and logout.
 */
void App::handleUserMenuUI(wxWindow* parent) {
    User user = SessionManager::getCurrentUser();

    // Dialog cho menu user
    wxDialog dlg(parent, wxID_ANY, "User Menu", wxDefaultPosition, wxSize(420, 420));
    dlg.SetBackgroundColour(wxColour(245, 247, 250));
    dlg.Centre();

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

    // Title
    wxString welcomeMsg = wxString::Format("Welcome, %s", wxString::FromUTF8(user.getUsername().c_str()));
    wxStaticText* title = new wxStaticText(&dlg, wxID_ANY, welcomeMsg);
    wxFont titleFont(wxFontInfo(20).Bold().FaceName("Arial"));
    title->SetFont(titleFont);
    title->SetForegroundColour(wxColour(44, 62, 80));
    vbox->Add(title, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 18);

    wxStaticText* subtitle = new wxStaticText(&dlg, wxID_ANY, "Please choose an action:");
    wxFont subFont(wxFontInfo(13).Italic().FaceName("Arial"));
    subtitle->SetFont(subFont);
    subtitle->SetForegroundColour(wxColour(52, 152, 219));
    vbox->Add(subtitle, 0, wxALIGN_CENTER | wxBOTTOM, 18);

    // Các nút chức năng
    wxButton* btnViewMovies   = new wxButton(&dlg, wxID_ANY, "View Movies");
    wxButton* btnFilterMovies = new wxButton(&dlg, wxID_ANY, "Filter Movies");
    wxButton* btnBookTicket   = new wxButton(&dlg, wxID_ANY, "Book Ticket");
    wxButton* btnShowTickets  = new wxButton(&dlg, wxID_ANY, "Show My Tickets");
    wxButton* btnLogout       = new wxButton(&dlg, wxID_EXIT, "Logout");

    wxFont btnFont(wxFontInfo(16).Bold().FaceName("Arial"));
    btnViewMovies->SetFont(btnFont);
    btnFilterMovies->SetFont(btnFont);
    btnBookTicket->SetFont(btnFont);
    btnShowTickets->SetFont(btnFont);
    btnLogout->SetFont(btnFont);

    btnViewMovies->SetBackgroundColour(wxColour(52, 152, 219));
    btnViewMovies->SetForegroundColour(*wxWHITE);
    btnFilterMovies->SetBackgroundColour(wxColour(46, 204, 113));
    btnFilterMovies->SetForegroundColour(*wxWHITE);
    btnBookTicket->SetBackgroundColour(wxColour(241, 196, 15));
    btnBookTicket->SetForegroundColour(*wxWHITE);
    btnShowTickets->SetBackgroundColour(wxColour(155, 89, 182));
    btnShowTickets->SetForegroundColour(*wxWHITE);
    btnLogout->SetBackgroundColour(wxColour(231, 76, 60));
    btnLogout->SetForegroundColour(*wxWHITE);

    btnViewMovies->SetMinSize(wxSize(320, 44));
    btnFilterMovies->SetMinSize(wxSize(320, 44));
    btnBookTicket->SetMinSize(wxSize(320, 44));
    btnShowTickets->SetMinSize(wxSize(320, 44));
    btnLogout->SetMinSize(wxSize(320, 44));

    btnViewMovies->SetWindowStyleFlag(wxBORDER_NONE);
    btnFilterMovies->SetWindowStyleFlag(wxBORDER_NONE);
    btnBookTicket->SetWindowStyleFlag(wxBORDER_NONE);
    btnShowTickets->SetWindowStyleFlag(wxBORDER_NONE);
    btnLogout->SetWindowStyleFlag(wxBORDER_NONE);

    vbox->Add(btnViewMovies,   0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    vbox->Add(btnFilterMovies, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnBookTicket,   0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnShowTickets,  0, wxALIGN_CENTER | wxBOTTOM, 10);
    vbox->Add(btnLogout,       0, wxALIGN_CENTER | wxTOP, 18);

    // Footer
    wxStaticText* footer = new wxStaticText(&dlg, wxID_ANY, "© 2025 Movie Ticket Booking | Designed by You");
    footer->SetForegroundColour(wxColour(160, 160, 160));
    wxFont footerFont(wxFontInfo(10).FaceName("Arial"));
    footer->SetFont(footerFont);
    vbox->Add(footer, 0, wxALIGN_CENTER | wxTOP, 18);

    dlg.SetSizerAndFit(vbox);

    // Gán command tương ứng với từng chức năng
    menu_invoker.setCommand(1, &view_movie_command);
    menu_invoker.setCommand(2, &filter_movie_command);
    menu_invoker.setCommand(3, &book_ticket_command);
    menu_invoker.setCommand(4, &show_ticket_command);

    // Sự kiện cho từng nút
    btnViewMovies->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(1, user, parent);
    });
    btnFilterMovies->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(2, user, parent);
    });
    btnBookTicket->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(3, user, parent);
    });
    btnShowTickets->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        menu_invoker.executeCommandUI(4, user,parent);
    });
    btnLogout->Bind(wxEVT_BUTTON, [&](wxCommandEvent&) {
        wxMessageBox("Logged out successfully!", "Notification", wxOK | wxICON_INFORMATION, &dlg);
        SessionManager::clear();
        dlg.EndModal(wxID_EXIT);
    });

    dlg.ShowModal();
}

/**
 * @brief Handles user registration in console mode, including OTP verification and rollback on failure.
 *
 * Architectural role: Orchestrates user creation, verification, and rollback using RollbackContainer.
 */
void App::handleRegister() {
    User user;
    std::string temp;

    std::cout << "Nhập tên đăng nhập: ";
    std::cin >> temp;
    user.setUsername(temp);
    
    std::cout << "Nhập mật khẩu: ";
    std::cin >> temp;
    user.setPassword(temp);
    
    std::cout << "Nhập số điện thoại: ";
    std::cin >> temp;
    user.setPhone(temp);
    
    std::cout << "Nhập email: ";
    std::cin >> temp;
    user.setEmail(temp);

    RollbackContainer rollback;
    auto res = user_service.createUser(user);

    if (res.status_code == StatusCode::SUCCESS) {
        rollback.addRollbackAction([&]() { user_service.removeUser(user); });
        rollback.addRollbackAction([&]() { SessionManager::clear(); });

        std::string otp;
        std::cout << "Nhập OTP: ";
        std::cin >> otp;

        while (user_service.verifyOTP(otp).status_code != StatusCode::OTP_VERIFICATION_SUCCESS) {
            int retry;
            std::cout << "Xác thực OTP thất bại. Thử lại? (1: Có, 0: Không): ";
            std::cin >> retry;
            if (retry == 0) break;
            std::cout << "Nhập lại OTP: ";
            std::cin >> otp;
        }

        if (user_service.verifyOTP(otp).status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
            std::cout << "Đăng ký thành công!\n";
        } else {
            std::cout << "Đăng ký thất bại. Đang rollback...\n";
            rollback.executeRollback();
            std::cout << "Rollback hoàn tất.\n";
        }
    } else {
        std::cout << "Đăng ký thất bại: " << res.message << "\n";
    }
}

/**
 * @brief Handles user registration in GUI mode, including OTP verification and rollback on failure.
 *
 * Architectural role: Orchestrates user creation, verification, and rollback using RollbackContainer in a wxWidgets dialog.
 */
void App::handleRegisterUI(const User& user, wxWindow* parent) {
    RollbackContainer rollback;
    auto res = user_service.createUser(user);

    if (res.status_code == StatusCode::SUCCESS) {
        rollback.addRollbackAction([&]() { user_service.removeUser(user); });
        rollback.addRollbackAction([&]() { SessionManager::clear(); });

        wxTextEntryDialog otpDlg(parent, "Enter OTP:", "OTP Verification");
        if (otpDlg.ShowModal() == wxID_OK) {
            std::string otp = otpDlg.GetValue().ToStdString();
            if (user_service.verifyOTP(otp).status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
                wxMessageBox("Register successfully!", "Notification", wxOK | wxICON_INFORMATION, parent);
            } else {
                wxMessageBox("OTP verification failed. Rolling back...", "Error", wxOK | wxICON_ERROR, parent);
                rollback.executeRollback();
                wxMessageBox("Rollback completed.", "Notification", wxOK | wxICON_INFORMATION, parent);
            }
        }
    } else {
        wxMessageBox(wxString::Format("Register failed: %s", res.message), "Error", wxOK | wxICON_ERROR, parent);
    }
}

/**
 * @brief Handles user login in console mode, including OTP verification.
 *
 * Architectural role: Authenticates user, manages session state, and routes to appropriate menu.
 */
void App::handleLogin() {
    User user;
    std::string temp;

    std::cout << "Nhập tên đăng nhập: ";
    std::cin >> temp;
    user.setUsername(temp);

    std::cout << "Nhập mật khẩu: ";
    std::cin >> temp;
    user.setPassword(temp);

    Logger::getInstance()->log("Authenticating user: " + user.getUsername(), Logger::Level::INFO);
    auto res = user_service.authenticateUser(user.getUsername(), user.getPassword());

    if (res.status_code == StatusCode::SUCCESS) {
        std::string otp;
        std::cout << "Nhập OTP: ";
        std::cin >> otp;

        Logger::getInstance()->log("Verifying OTP: " + otp, Logger::Level::INFO);
        
        while (user_service.verifyOTP(otp).status_code != StatusCode::OTP_VERIFICATION_SUCCESS) {
            int retry;
            std::cout << "Xác thực OTP thất bại. Thử lại? (1: Có, 0: Không): ";
            std::cin >> retry;
            if (retry == 0) break;
            std::cout << "Nhập lại OTP: ";
            std::cin >> otp;
        }
        if (user_service.verifyOTP(otp).status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
            std::cout << "Đăng nhập thành công!\n";
            SessionManager::setLoggedIn(true);
        } 
        
        else {
            std::cout << "Xác thực OTP thất bại: " << res.message << "\n";
            SessionManager::clear();   
        }
        

    } else if (res.status_code == StatusCode::USER_NOT_FOUND) {
        std::cout << "Người dùng không tồn tại!\n";
    } else if (res.status_code == StatusCode::INVALID_PASSWORD) {
        std::cout << "Mật khẩu không đúng!\n";
    } else {
        std::cout << "Đăng nhập thất bại: " << res.message << "\n";
    }
}

/**
 * @brief Handles user login in GUI mode, including OTP verification.
 *
 * Architectural role: Authenticates user, manages session state, and routes to appropriate menu in a wxWidgets dialog.
 */
void App::handleLoginUI(const std::string& username, const std::string& password, wxWindow* parent) {
    Logger::getInstance()->log("Authenticating user: " + username, Logger::Level::INFO);
    auto res = user_service.authenticateUser(username, password);

    if (res.status_code == StatusCode::SUCCESS) {
        wxTextEntryDialog otpDlg(parent, "Enter OTP:", "OTP Verification");
        if (otpDlg.ShowModal() == wxID_OK) {
            std::string otp = otpDlg.GetValue().ToStdString();
            Logger::getInstance()->log("Verifying OTP: " + otp, Logger::Level::INFO);

            if (user_service.verifyOTP(otp).status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
                wxMessageBox("Login successful!", "Notification", wxOK | wxICON_INFORMATION, parent);
                SessionManager::setLoggedIn(true);

                // Kiểm tra quyền và mở menu phù hợp
                if (SessionManager::isAdminUser()) {
                    handleAdminMenuUI(parent);
                } else {
                    handleUserMenuUI(parent);
                }
            } else {
                wxMessageBox("OTP verification failed!", "Error", wxOK | wxICON_ERROR, parent);
                SessionManager::clear();
            }
        }
    } else if (res.status_code == StatusCode::USER_NOT_FOUND) {
        wxMessageBox("User not found!", "Error", wxOK | wxICON_ERROR, parent);
    } else if (res.status_code == StatusCode::INVALID_PASSWORD) {
        wxMessageBox("Invalid password!", "Error", wxOK | wxICON_ERROR, parent);
    } else {
        wxMessageBox(wxString::Format("Login failed: %s", res.message), "Error", wxOK | wxICON_ERROR, parent);
    }
}

/**
 * @brief Handles application exit and cleanup.
 *
 * Architectural role: Ensures graceful shutdown and logs exit event.
 */
void App::handleExit() {
    Logger::getInstance()->log("User chose to exit the application", Logger::Level::INFO);
    std::cout << "Tạm biệt!\n";
    exit(0);
}

/**
 * @brief Displays the start menu and handles initial user choices.
 *
 * Architectural role: Entry point for user interaction, routes to registration, login, or exit.
 */
void App::displayStartMenu() {
    std::cout << "===== CINEMA BOOKING SYSTEM =====\n";
    std::cout << "1. Đăng ký\n";
    std::cout << "2. Đăng nhập\n";
    std::cout << "0. Thoát\n";
    std::cout << "Nhập lựa chọn của bạn: ";
}


