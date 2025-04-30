#include "../../include/repositories/SeatRepository.h"

Result<vector<Seat>> SeatRepository::findByRoomId(int id_room, int id_theater) {
    Result<vector<Seat>> result;
    std::string query = "SELECT * FROM Seat WHERE roomID = " + std::to_string(id_room) + " AND theaterID = " + std::to_string(id_theater);
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    vector<Seat> seats;
    while ((row = mysql_fetch_row(res))) {
        int id_room_in_dtb = row[0] ? atoi(row[0]) : 0;
        int id_theater_in_dtb = row[1] ? atoi(row[1]) : 0;
        string seat_number = row[2] ? row[2] : "";
        bool is_vip = row[3] ? (atoi(row[3]) == 1) : false;
        Seat seat(id_room_in_dtb, id_theater_in_dtb, seat_number, is_vip);
        seats.push_back(seat);
    }
    result.success = true;
    result.data = seats;
    return result;
}