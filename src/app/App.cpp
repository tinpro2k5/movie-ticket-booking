#include "../../include/app/App.h"

App::App():
        repos_res(),
        user_service(repos_res)
{}
int App::run() {
    ServerInfo serverInfo;
    DatabaseManager::getInstance()->connect(serverInfo);
    DatabaseManager::getInstance()->setupDatabase();
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

                auto res = user_service.createUser(user);
                if (res.status_code == StatusCode::SUCCESS) {
                    std::cout << "Đăng ký thành công!\n";
                } else {
                    std::cout << "Đăng ký thất bại: " << res.message << "\n";
                }
                break;

            }
            case 2:

                break;
            case 0:
                return 0;
            default:
                std::cout << "Lựa chọn không hợp lệ!\n";
        }
    }
}