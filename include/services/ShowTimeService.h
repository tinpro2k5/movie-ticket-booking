#ifndef    SHOWTIMESERVICE_H
#define    SHOWTIMESERVICE_H
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/repositories/TicketRepository.h"


class ShowTimeService {
    std::shared_ptr<ShowTimeRepository> show_time_repos;
    std::shared_ptr<SeatScheduleRepository> seat_schedule_repos;
    std::shared_ptr<UserRepository> user_repos;
    std::shared_ptr<TicketRepository> ticket_repos;
public:
    ShowTimeService(RepositoryRegistry& repoRegistry) {
        show_time_repos = std::dynamic_pointer_cast<ShowTimeRepository>(repoRegistry.show_time_repos);
        seat_schedule_repos = std::dynamic_pointer_cast<SeatScheduleRepository>(repoRegistry.seat_schedule_repos);
        user_repos = std::dynamic_pointer_cast<UserRepository>(repoRegistry.user_repos);
        ticket_repos = std::dynamic_pointer_cast<TicketRepository>(repoRegistry.ticket_repos);
        if (!show_time_repos || !seat_schedule_repos || !user_repos || !ticket_repos) {
            throw std::runtime_error("Failed to initialize ShowTimeService: Repositories not found");
        }
    }
    void manageShowTime(User user) {
        std::cout << "===== QUẢN LÝ LỊCH CHIẾU =====\n";
        std::cout << "1. Thêm lịch chiếu\n";
        std::cout << "2. Xóa lịch chiếu\n";
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