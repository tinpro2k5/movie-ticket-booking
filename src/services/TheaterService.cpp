#include "../../include/services/TheaterService.h"

TheaterService::TheaterService(RepositoryRegistry& repoRegistry) {
    movie_theater_repos = std::dynamic_pointer_cast<MovieTheaterRepository>(repoRegistry.movie_theater_repos);
    if (!movie_theater_repos) {
        Logger::getInstance()->log("Failed to cast to MovieTheaterRepository", Logger::Level::ERROR);
        std::cerr << "Failed to cast to MovieTheaterRepository" << std::endl;
    }
}

void TheaterService::manageTheater(User user) {
    std::cout << "===== QUẢN LÝ RẠP =====\n";
    std::cout << "1. Thêm rạp\n";
    std::cout << "2. Xem danh sách rạp\n";
    std::cout << "0. Thoát\n";
    std::cout << "========================\n";
    int choice;
    cout << "Nhập lựa chọn của bạn: ";
    std::cin >> choice;
    switch (choice) {
        case 1: {
            MovieTheater theater;
            std::cin.ignore();
            std::cout << "Nhập tên rạp: ";
            std::string name;
            std::getline(std::cin, name);
            theater.setTheaterName(name);
            std::cout << "Nhập địa chỉ rạp: ";
            std::string location;
            std::getline(std::cin, location);
            theater.setTheaterLocation(location);
            Result<int> result = movie_theater_repos->create(theater);
            if (!result.success) {
                std::cout << result.error_message << "\n";
                return;
            } else {
                std::cout << "Thêm rạp thành công \n";
            }
            break;
        }
        case 2: {
            vector<MovieTheater> theaters = movie_theater_repos->findAll().data;
            printTheaterTable(theaters);
            break;
        }
        default:
            return;
    }
}