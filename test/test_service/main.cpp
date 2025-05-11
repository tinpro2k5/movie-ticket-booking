#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"
#include "../../include/services/ViewMovieCommand.h"
#include "../../include/services/FilterMovieCommand.h"
#include "../../include/services/MenuInvoker.h"
#include "../../include/services/TicketService.h"
#include "../../include/services/BookTicketCommand.h"
#include "../../include/services/ShowTicketCommand.h"
/* Compile
g++ src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/RepositoryRegistry.cpp test/test_service/main.cpp -o test/test_service/main -lmysqlclient
 */
int main() {
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    User user(3, "jane_doe", "password456", "jane@example.com", "0111222333", false);
    int choice;
    RepositoryRegistry repos_res;
    MovieService movieService(repos_res);
    TicketService ticketService(repos_res);
    //
    ViewMovieCommand viewMovies(&movieService);
    FilterMovieCommand filterMovies(&movieService);
    BookTicketCommand bookTicket(&ticketService);
    ShowTicketCommand viewTickets(&ticketService);
    //
    MenuInvoker menu;
    menu.setCommand(1, &viewMovies);
    menu.setCommand(2, &filterMovies);
    menu.setCommand(3, &bookTicket);
    menu.setCommand(4, &viewTickets);
    do {
        menu.showMenuUser();
        std::cout << "Chọn chức năng: ";
        std::cin >> choice;
        if (choice != 0)
            menu.executeCommand(choice, user);
    } while (choice != 0);

    return 0;
}

// App::App():
//         repos_res(),
//         user_service(repos_res)
// {}
// App::~App() {
//     // Destructor
//     // Clean up resources if needed
// }
// int App::run() {
//     ServerInfo serverInfo;
//     DatabaseManager::getInstance()->connect(serverInfo);
//     DatabaseManager::getInstance()->setupDatabase();
//     std::cout << "===== CINEMA BOOKING SYSTEM =====\n";
//     int choice;
//     while (true) {
//         startMenu();
//         std::cin >> choice;
//         User user;
//         switch (choice) {
//             case 1: {
//                 string temp;
//                 std::cout << "Nhập tên đăng nhập: ";
//                 std::cin >> temp;
//                 user.setUsername(temp);
//                 std::cout << "Nhập mật khẩu: ";
//                 std::cin >> temp;
//                 user.setPassword(temp);
    
//                 std::cout << "Nhập số điện thoại: ";
//                 std::cin >> temp;
//                 user.setPhone(temp);
//                 std::cout << "Nhập email: ";
//                 std::cin >> temp;
//                 user.setEmail(temp);

//                 auto res = user_service.createUser(user);
//                 if (res.status_code == StatusCode::SUCCESS) {
//                     std::cout << "Đăng ký thành công!\n";
//                 } else {
//                     std::cout << "Đăng ký thất bại: " << res.message << "\n";
//                 }
//                 break;

//             }
//             case 2: {
//                 User user;
//                 std::string temp;
//                 std::cout << "Nhập tên đăng nhập: ";
//                 std::cin >> temp;
//                 user.setUsername(temp);
//                 std::cout << "Nhập mật khẩu: ";
//                 std::cin >> temp;
//                 user.setPassword(temp);
//                 auto res = user_service.authenticateUser(user.getUsername(), user.getPassword());
//                 if (res.status_code == StatusCode::SUCCESS) {
//                     std::cout <<"Nhap OTP: ";
//                     std::string otp;
//                     std::cin >> otp;
//                     auto otp_res = user_service.verifyOTP(otp);
//                     if (otp_res.status_code == StatusCode::OTP_VERIFICATION_SUCCESS) {
//                         std::cout << "Đăng nhập thành công!\n";
//                         user_service.getUserByUsername(user.getUsername());
//                     } else {
//                         std::cout << "Xác thực OTP thất bại: " << otp_res.message << "\n";
//                     }
//                 }
//                 else if (res.status_code == StatusCode::USER_NOT_FOUND) {
//                     std::cout << "Người dùng không tồn tại!\n";
//                 } else if (res.status_code == StatusCode::INVALID_PASSWORD) {
//                     std::cout << "Mật khẩu không đúng!\n";
//                 } else {
//                     std::cout << "Đăng nhập thất bại: " << res.message << "\n";
//                 }
//                 break;
//             }
//             case 0:
//                 return 0;
//             default:
//                 std::cout << "Lựa chọn không hợp lệ!\n";
//         }
//     }
// }