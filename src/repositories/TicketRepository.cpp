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