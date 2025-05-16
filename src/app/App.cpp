#include "../../include/app/App.h"

App::App():
        repos_res(),
        user_service(repos_res),
        movie_service(repos_res),
        ticket_service(repos_res),
        show_time_service(repos_res),
        room_service(repos_res),
        theater_service(repos_res),
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
    Logger::getInstance()->setLogFile(Logger::getInstance()->DEFAULT_LOG_FILE);
    Logger::getInstance()->log("App initialized", Logger::Level::INFO);
}
App::~App() {
    Logger::getInstance()->log("App destroyed", Logger::Level::INFO);
    // Destructor
    // Clean up resources if needed
}
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
        system("pause");
        system("clear");
    }
    }


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

void App::handleExit() {
    Logger::getInstance()->log("User chose to exit the application", Logger::Level::INFO);
    std::cout << "Tạm biệt!\n";
    exit(0);
}


void App::displayStartMenu() {
    std::cout << "===== CINEMA BOOKING SYSTEM =====\n";
    std::cout << "1. Đăng ký\n";
    std::cout << "2. Đăng nhập\n";
    std::cout << "0. Thoát\n";
    std::cout << "Nhập lựa chọn của bạn: ";
}


