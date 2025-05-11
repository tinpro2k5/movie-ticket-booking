#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include "../../include/repositories/TicketRepository.h"
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/models/User.h"
#include "../../include/repositories/SeatScheduleRepository.h"
class TicketService{
    std::shared_ptr<TicketRepository> ticket_repos;
    public:
    TicketService(RepositoryRegistry& repoRegistry){
        ticket_repos = std::dynamic_pointer_cast<TicketRepository>(repoRegistry.ticket_repos);
        if (!ticket_repos) {
            Logger::getInstance()->log("Failed to cast to TicketRepository", Logger::Level::ERROR);
            std::cerr << "Failed to cast to TicketRepository" << std::endl;
        }
    }
    void bookTicket(User user) {
        ShowTimeRepository showtime_repos;
        int id;
        //Nhap phim muon dat
        cout << "Nhap ID phim muon dat: ";
        std::cin >> id;
        Result<vector<ShowTime>> result = showtime_repos.findShowTimeByMovieId(id);
    
        if (!result.success || result.data.empty()) {
            cout << "Khong tim thay xuat chieu cho phim nay.\n";
            return;
        }
    
        cout << "Cac xuat chieu co cua phim:\n";
        for (int i = 0; i < result.data.size(); i++) {
            std::cout << "Room ID: " << result.data[i].getRoomId() << std::endl;
            std::cout << "Theater ID: " << result.data[i].getTheaterId() << std::endl;
            std::cout << "Show Time: " << result.data[i].getShowTime() << std::endl;
        }
        //Nhap gio dat
        std::cin.ignore();
        string showtime;
        cout << "Nhap gio can dat theo list tren: ";
        getline(std::cin, showtime);
        if (showtime.empty()) return;
        //Tim xuat chieu
        Result<ShowTime> showtime_result = showtime_repos.findExactlyShowTime(id, showtime);
        if (!showtime_result.success) {
            cout << "Khong tim thay xuat chieu.\n";
            return;
        }
        //Tim ghe 
        SeatScheduleRepository ss_repos;
        Result<vector<SeatSchedule>> ss_result = ss_repos.findAvailableSeats(
            showtime_result.data.getRoomId(),
            showtime_result.data.getTheaterId(),
            showtime_result.data.getShowTime());
    
        if (!ss_result.success || ss_result.data.empty()) {
            cout << "Khong con ghe trong.\n";
            return;
        }
        cout << "Cac ghe con trong: ";
        for (const auto& ss : ss_result.data) {
            cout << ss.getSeatNumber() << " ";
        }
        cout << "\n";
        //Chon ghe
        string seat_number;
        cout << "Chon so ghe theo list tren: ";
        getline(std::cin, seat_number);
        
        Ticket cur_ticket(
            1, user.getUserId(),
            showtime_result.data.getRoomId(),
            showtime_result.data.getTheaterId(),
            seat_number,
            showtime_result.data.getShowTime(),
            100.0,
            "", true
        );
        // Lưu ticket và lấy ticket ID vừa tạo
        Result<int> insert_result = ticket_repos->create(cur_ticket);
        if (!insert_result.success) {
            cout << "Dat ve that bai: " << insert_result.error_message << "\n";
            return;
        }
    
        int ticket_id = insert_result.data;
        SeatSchedule seat_to_update(
            showtime_result.data.getRoomId(),
            showtime_result.data.getTheaterId(),
            seat_number,
            showtime_result.data.getShowTime(),
            ticket_id
        );
        Result<bool> update_result = ss_repos.update(seat_to_update);
        if (!update_result.success) {
            cout << "Cap nhat SeatSchedule that bai: " << update_result.error_message << "\n";
            return;
        }
        cout << 1;
        cout << "Dat ve thanh cong! Ma ve: " << ticket_id << "\n";
    }
        void viewUserTicket(User user){
        Result<vector<Ticket>> result = ticket_repos->findByUserId(user.getUserId());
        if(!result.success){
            cout << result.error_message << "\n";
            return;
        }
        const vector<Ticket>& tickets = result.data;
        if(tickets.empty()){
            cout << "Khong co ve cua ban trong CSDL \n";
            return;
        }
        cout << "All tickets you have bought.\n";
        for (int i = 0; i < tickets.size(); i++) {
            cout << "Ticket ID: " << result.data[i].getTicketId() << endl;
            cout << "User ID: " << result.data[i].getUserId() << endl;
            cout << "Room ID: " << result.data[i].getRoomId() << endl;
            cout << "Theater ID: " << result.data[i].getTheaterId() << endl;
            cout << "Seat Number: " << result.data[i].getSeatNumber() << endl;
            cout << "Show Time: " << result.data[i].getShowTime() << endl;
            cout << "Price: " << result.data[i].getPrice() << endl;
            cout << "Booking Time: " << result.data[i].getBookingTime() << endl;
            cout << "Is Paid: " << (result.data[i].isPaid() ? "Yes" : "No") << endl;
        }
    }
};
#endif