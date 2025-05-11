#ifndef    SHOWTIMESERVICE_H
#define    SHOWTIMESERVICE_H
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/app/RepositoryRegistry.h"

class ShowTimeService {
    std::shared_ptr<ShowTimeRepository> show_time_repos;
    std::shared_ptr<SeatScheduleRepository> seat_schedule_repos;
public:
    ShowTimeService(RepositoryRegistry& repoRegistry) {
        show_time_repos = std::dynamic_pointer_cast<ShowTimeRepository>(repoRegistry.show_time_repos);
        seat_schedule_repos = std::dynamic_pointer_cast<SeatScheduleRepository>(repoRegistry.seat_schedule_repos);
        if (!show_time_repos) {
            Logger::getInstance()->log("Failed to cast to ShowTimeRepository", Logger::Level::ERROR);
            std::cerr << "Failed to cast to ShowTimeRepository" << std::endl;
        }
        if (!show_time_repos) {
            Logger::getInstance()->log("Failed to cast to ShowTimeRepository", Logger::Level::ERROR);
            std::cerr << "Failed to cast to ShowTimeRepository" << std::endl;
        }
    }
    void manageShowTime(User& user) {
        std::cout << "===== QUẢN LÝ LỊCH CHIẾU =====\n";
        std::cout << "1. Thêm lịch chiếu\n";
        std::cout << "2. Cập nhật lịch chiếu\n";
        std::cout << "3. Xem lịch chiếu\n";
        std::cout << "0. Thoát\n";
        std::cout << "=============================\n";
        int choice;
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
                std::cout << "Nhập ID phim cần cập nhật: ";
                int id;
                std::cin >> id;
                while (id < 1) {
                    std::cout << "ID không hợp lệ! Nhập lại ID > 1\n";
                    std::cin >> id;
                }
                std::cin.ignore();
                std::cout << "Nhập thời gian chiếu cần sửa (YYYY-MM-DD HH:MM:SS): ";
                std::string old_show_time;
                std::getline(std::cin, old_show_time);

                Result<ShowTime> result = show_time_repos->findExactlyShowTime(id, old_show_time);
                if (!result.success) {
                    std::cout << result.error_message << "\n";
                    return;
                }

                ShowTime showtime = result.data;
                int room_id = showtime.getRoomId();
                int theater_id = showtime.getTheaterId();

                std::string delete_query = "DELETE FROM SeatSchedule WHERE roomID = " +
                std::to_string(room_id) + " AND theaterID = " +
                std::to_string(theater_id) + " AND showDateTime = '" + old_show_time + "'";
                DatabaseManager::getInstance()->executeQuery(delete_query);

                std::string delete_showtime_query = "DELETE FROM Showtime WHERE roomID = " +
                std::to_string(room_id) + " AND theaterID = " + std::to_string(theater_id) + 
                " AND showDateTime = '" + old_show_time + "'";
                DatabaseManager::getInstance()->executeQuery(delete_showtime_query);

                // Kiểm tra xem thời gian chiếu mới có trùng với thời gian chiếu hiện tại không
                std::cout << "Nhập thời gian chiếu mới (YYYY-MM-DD HH:MM:SS): ";
                std::string new_show_time;
                std::getline(std::cin, new_show_time);

                // Kiểm tra sự tồn tại của thời gian chiếu mới
                Result<ShowTime> check_result = show_time_repos->findExactlyShowTime(id, new_show_time);
                if (check_result.success) {
                    std::cout << "Thời gian chiếu mới đã tồn tại. Vui lòng chọn thời gian khác.\n";
                    return;
                }

                // Cập nhật thời gian chiếu
                showtime.setShowTime(new_show_time);
                Result<int> update_result = show_time_repos->create(showtime);
                if (!update_result.success) {
                    std::cout << update_result.error_message << "\n";
                    return;
                }



                // Thêm lại ghế theo thời gian mới
                SeatSchedule seat_schedule(room_id, theater_id, "", new_show_time, 0);
                vector<string> seat_numbers = {
                    "A1", "A2", "A3", "A4", "A5",
                    "B1", "B2", "B3", "B4", "B5",
                    "C1", "C2", "C3", "C4", "C5"
                };
                for (const auto& seat : seat_numbers) {
                    seat_schedule.setSeatNumber(seat);
                    Result<int> insert_result = seat_schedule_repos->create(seat_schedule);
                    if (!insert_result.success) {
                        std::cout << "Thêm ghế thất bại: " << insert_result.error_message << "\n";
                        return;
                    }
                }

                std::cout << "Cập nhật lịch chiếu thành công \n";
                break;
            }
            case 3: {
                cout << "====Xem lịch chiếu====\n";
                cout << "1. Theo ID phim\n";
                cout << "2. Theo ID rạp\n";
                cout << "0. Thoát\n";
                cout << "=====================\n";
                int choice;
                std::cin >> choice;
                switch (choice) {
                    case 1: {
                        std::cout << "Nhập ID phim: ";
                        int movie_id;
                        std::cin >> movie_id;
                        Result<vector<ShowTime>> result = show_time_repos->findShowTimeByMovieId(movie_id);
                        if (!result.success) {
                            std::cout << result.error_message << "\n";
                            return;
                        }
                        for (const auto& showtime : result.data) {
                            std::cout << "Room ID: " << showtime.getRoomId() << std::endl;
                            std::cout << "Theater ID: " << showtime.getTheaterId() << std::endl;
                            std::cout << "Show Time: " << showtime.getShowTime() << std::endl;
                            std::cout << "Movie ID: " << showtime.getMovieId() << std::endl;
                        }
                        break;
                    }
                    case 2: {
                        std::cout << "Nhập ID rạp: ";
                        int theater_id;
                        std::cin >> theater_id;
                        Result<vector<ShowTime>> result = show_time_repos->findShowTimeByTheaterId(theater_id);
                        if (!result.success) {
                            std::cout << result.error_message << "\n";
                            return;
                        }
                        for (const auto& showtime : result.data) {
                            std::cout << "Room ID: " << showtime.getRoomId() << std::endl;
                            std::cout << "Theater ID: " << showtime.getTheaterId() << std::endl;
                            std::cout << "Show Time: " << showtime.getShowTime() << std::endl;
                            std::cout << "Movie ID: " << showtime.getMovieId() << std::endl;
                        }
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
};
#endif