#include "../../include/repositories/TicketRepository.h"

Result<Ticket> TicketRepository::findById(int ticket_id){
    std::string query = "SELECT * FROM Ticket WHERE ticketID = " + std::to_string(ticket_id);
    Result<Ticket> result;
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    if ((row = mysql_fetch_row(res))) {
        int id_ticket = row[0] ? atoi(row[0]) : 0;
        int id_user = row[1] ? atoi(row[1]) : 0;
        int id_room = row[2] ? atoi(row[2]) : 0;
        int id_theater = row[3] ? atoi(row[3]) : 0;
        string seat_number = row[4] ? row[4] : "";
        string show_time = row[5] ? row[5] : "";
        double price = row[6] ? atof(row[6]) : 0.0;
        string booking_time = row[7] ? row[7] : "";
        bool is_paid = row[8] ? (atoi(row[8]) == 1) : false;

        Ticket ticket(id_ticket, id_user, id_room, id_theater, seat_number, show_time, price, booking_time, is_paid);
        result.success = true;
        result.data = ticket;
    } else {
        result.success = false;
        result.error_message = "Ticket not found";
    }
    return result;
}
Result<vector<Ticket>> TicketRepository::findByUserId(int user_id){
    std::string query = "SELECT * FROM Ticket WHERE userID = " + std::to_string(user_id);
    Result<vector<Ticket>> result;
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    vector<Ticket> tickets;
    while ((row = mysql_fetch_row(res))) {
        int id_ticket = row[0] ? atoi(row[0]) : 0;
        int id_user = row[1] ? atoi(row[1]) : 0;
        int id_room = row[2] ? atoi(row[2]) : 0;
        int id_theater = row[3] ? atoi(row[3]) : 0;
        string seat_number = row[4] ? row[4] : "";
        string show_time = row[5] ? row[5] : "";
        double price = row[6] ? atof(row[6]) : 0.0;
        string booking_time = row[7] ? row[7] : "";
        bool is_paid = row[8] ? (atoi(row[8]) == 1) : false;

        Ticket ticket(id_ticket, id_user, id_room, id_theater, seat_number, show_time, price, booking_time, is_paid);
        tickets.push_back(ticket);
    }
    result.success = true;
    result.data = tickets;
    return result;
}
Result<int> TicketRepository::create(const Ticket& ticket){
        //Thuc hien truy van
        Result<int> result;
        string paid = (ticket.isPaid()) ? "TRUE" : "FALSE";
        std::string query = "INSERT IGNORE INTO Ticket (userID, roomID, theaterID, seatNumber, showDateTime, basePrice, isPaid) VALUES ('" +
        std::to_string(ticket.getUserId()) + "', '" +
        std::to_string(ticket.getRoomId()) + "', '" +
        std::to_string(ticket.getTheaterId()) + "', '" +
        ticket.getSeatNumber() + "', '" +
        ticket.getShowTime() + "', '" +
        std::to_string(ticket.getPrice()) + "', " +
        paid + ")";

        QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
        /*Kiem tra ket qua truy van
        Neu khong thanh cong, tra ve ket qua that bai*/
        if (!query_result.success) {
            result.success = false;
            result.error_message = query_result.error_message;
            return result;
        }
        /*Neu thanh cong, kiem tra so dong bi anh huong
        Neu so dong bi anh huong > 0, tra ve ket qua thanh cong
        Neu so dong bi anh huong = 0, tra ve ket qua that bai*/
        if (query_result.affected_rows > 0) {
            result.success = true;
            QueryResult id_result = DatabaseManager::getInstance()->executeQuery("SELECT LAST_INSERT_ID() AS id");
            if (id_result.success && id_result.result) {
                MYSQL_ROW row = mysql_fetch_row(id_result.result.get());
                if (row && row[0]) {
                    result.data = std::stoi(row[0]); // ép kiểu chuỗi sang số
                } else {
                    result.success = false;
                    result.error_message = "Không đọc được ticketID.";
                }
            } else {
                result.success = false;
                result.error_message = "Không thể thực hiện truy vấn lấy ticketID.";
            }
        } else {
            result.success = false;
            result.error_message = "Failed to ticket";
        }
        return result;
}

Result<std::vector<Ticket>> TicketRepository::findHavingShowTime(const ShowTime& showtime) {
    Result<std::vector<Ticket>> result;

    std::string query = "SELECT * FROM Ticket WHERE roomID = " + std::to_string(showtime.getRoomId()) +
                        " AND theaterID = " + std::to_string(showtime.getTheaterId()) +
                        " AND showDateTime = '" + showtime.getShowTime() + "'";

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

    MYSQL_ROW row;
    MYSQL_RES* res = query_result.result.get();
    std::vector<Ticket> tickets;

    while ((row = mysql_fetch_row(res))) {
        int ticketId      = row[0] ? std::atoi(row[0]) : 0;
        int userId        = row[1] ? std::atoi(row[1]) : 0;
        int roomId        = row[2] ? std::atoi(row[2]) : 0;
        int theaterId     = row[3] ? std::atoi(row[3]) : 0;
        std::string seat  = row[4] ? row[4] : "";
        std::string time  = row[5] ? row[5] : "";
        double basePrice  = row[6] ? std::atof(row[6]) : 0.0;
        std::string bookedAt = row[7] ? row[7] : "";
        bool isPaid       = row[8] ? (std::atoi(row[8]) == 1) : false;

        tickets.emplace_back(ticketId, userId, roomId, theaterId, seat, time, basePrice, bookedAt, isPaid);
    }

    result.success = true;
    result.data = tickets;
    return result;
}
