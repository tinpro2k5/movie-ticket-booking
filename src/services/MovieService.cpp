// #include "../../include/services/MovieService.h"

// MovieService::MovieService() {

// }

// MovieService::~MovieService() {
    
// }
// void MovieService::manageMovieMenu() {
//     int choice;
//     while (true) {
//         std::cout << "===== Movie Management Menu =====\n";
//         std::cout << "1. Add Movie\n";
//         std::cout << "2. Edit Movie\n";
//         std::cout << "3. Delete Movie\n";
//         std::cout << "4. List Movies\n";
//         std::cout << "0. Back to Main Menu\n";
//         std::cin >> choice;

//         switch (choice) {
//             case 1:
//                 addMovie();
//                 break;
//             case 2:
//                 editMovie();
//                 break;
//             case 3:
//                 deleteMovie();
//                 break;
//             case 4:
//                 listMovies();
//                 break;
//             case 0:
//                 return;  // Quay lại menu chính
//             default:
//                 std::cout << "Invalid choice! Please try again.\n";
//         }
//     }
// }

// void MovieService::addMovie() {
//     // Gọi phương thức addNewMovie của MovieRepositories để thêm phim vào cơ sở dữ liệu
//     movie_repos.addNewMovie();
// }

// void MovieService::editMovie() {
//     // Gọi phương thức editMovie của MovieRepositories để chỉnh sửa phim
//     movie_repos.editMovie();
// }

// void MovieService::deleteMovie() {
//     // Gọi phương thức deleteMovie của MovieRepositories để xóa phim
//     movie_repos.deleteMovie();
// }

// void MovieService::listMovies() {
//     // Gọi phương thức listMovies của MovieRepositories để liệt kê các phim
//     movie_repos.showMovieList();
// }
