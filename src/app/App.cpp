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
    DatabaseManager::getInstance()->setupDatabase();
    cout << "------------------------------------------\n";
    std::cout << "===== CINEMA BOOKING SYSTEM =====\n";
    int choice;
    while (true) {
        startMenu();
        std::cin >> choice;
        User user;
        switch (choice) {
            case 1: {
                string temp;
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
                Logger::getInstance()->log("Creating user: " + user.getUsername(), Logger::Level::INFO);
                auto res = user_service.createUser(user);
                if (res.status_code == StatusCode::SUCCESS) {
                    std::cout << "Đăng ký thành công!\n";
                } else {
                    std::cout << "Đăng ký thất bại: " << res.message << "\n";
                }
                break;

            }
            case 2: {
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
                    std::cout <<"Nhap OTP: ";
                    std::string otp;
                    std::cin >> otp;
                    Logger::getInstance()->log("Verifying OTP: " + otp, Logger::Level::INFO);
                    auto otp_res = user_service.verifyOTP(otp);
                    if (otp_res.status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
                        std::cout << "Đăng nhập thành công!\n";
                        ServiceResult<User> result = user_service.getUserByUsername(user.getUsername());
                        user = result.data;
                        if(user.getIsAdmin()){
                            menu_invoker.setCommand(1, &movie_manage_command);
                            menu_invoker.setCommand(2, &show_time_manage_command);
                            menu_invoker.setCommand(3, &theater_manage_commnand);
                            menu_invoker.setCommand(4, &room_manage_commnand);
                            do {
                                menu_invoker.showMenuAdmin();
                                std::cout << "Chọn chức năng: ";
                                std::cin >> choice;
                                if (choice != 0)
                                    menu_invoker.executeCommand(choice, user);
                            } while (choice != 0);
                        }else{
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
                        }
                    } else {
                        std::cout << "Xác thực OTP thất bại: " << otp_res.message << "\n";
                    }
                }
                else if (res.status_code == StatusCode::USER_NOT_FOUND) {
                    std::cout << "Người dùng không tồn tại!\n";
                } else if (res.status_code == StatusCode::INVALID_PASSWORD) {
                    std::cout << "Mật khẩu không đúng!\n";
                } else {
                    std::cout << "Đăng nhập thất bại: " << res.message << "\n";
                }
                break;
            }
            case 0:
                return 0;
            default:
                std::cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}