#include "../../include/repositories/SeatScheduleRepository.h"

Result<vector<SeatSchedule>> SeatScheduleRepository::findAvailableSeats(int id_room, int id_theater, string show_time){
    std::string query = "SELECT * FROM SeatSchedule WHERE roomID = " + std::to_string(id_room) + " AND theaterID = " + std::to_string(id_theater) + " AND showDateTime = '" + show_time + "' AND ticketID IS NULL;";
    Result<vector<SeatSchedule>> result;
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    vector<SeatSchedule> seat_schedules;
    while ((row = mysql_fetch_row(res))) {
        int id_room = row[0] ? atoi(row[0]) : 0;
        int id_theater = row[1] ? atoi(row[1]) : 0;
        string seat_number = row[2] ? row[2] : "";
        string show_time = row[3] ? row[3] : "";
        int id_ticket = row[4] ? atoi(row[4]) : 0;

        SeatSchedule seat_schedule(id_room, id_theater, seat_number, show_time, id_ticket);
        seat_schedules.push_back(seat_schedule);
    }
    result.success = true;
    result.data = seat_schedules;
    return result;
}
Result<bool> SeatScheduleRepository::findSeatById(int id_room, int id_theater, string seat_number, string show_time){
    std::string query = "SELECT * FROM SeatSchedule WHERE roomID = " + std::to_string(id_room) + " AND theaterID = " + std::to_string(id_theater) + " AND seatNumber = '" + seat_number + "' AND showDateTime = '" + show_time + "';";
    Result<bool> result;
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row[4] == nullptr){
        result.success = true;
        result.data = true;
    }else{
        result.success = true;
        result.data = false;
    }
    return result;
}