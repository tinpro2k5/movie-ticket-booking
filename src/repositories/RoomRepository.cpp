#include "include/repositories/RoomRepository.h"

Result<vector<Room>> RoomRepository::findByTheaterId(int id_theater){
    Result<vector<Room>> result;
    std::string query = "SELECT * FROM Room WHERE theaterID = " + std::to_string(id_theater);
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);

    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    vector<Room> rooms;

    while((row = mysql_fetch_row(res))) {
        int id_room_in_dtb = row[0] ? atoi(row[0]) : 0;
        int id_theater_in_dtb = row[1] ? atoi(row[1]) : 0;
        string room_name = row[2] ? row[2] : "";
        int capacity = row[3] ? atoi(row[3]) : 0;
        Room room(id_room_in_dtb, id_theater_in_dtb, room_name, capacity);
        rooms.push_back(room);
    }

    result.success = true;
    result.data = rooms;
    return result;
}
Result<Room> RoomRepository::findById(int id_theater, int id_room){
    Result<Room> result;
    std::string query = "SELECT * FROM Room WHERE theaterID = " + std::to_string(id_theater) + " AND roomID = " + std::to_string(id_room);
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);

    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row = mysql_fetch_row(res);

    if (!row) {
        result.success = false;
        result.error_message = "Room not found";
        return result;
    }

    int id_room_in_dtb = row[0] ? atoi(row[0]) : 0;
    int id_theater_in_dtb = row[1] ? atoi(row[1]) : 0;
    string room_name = row[2] ? row[2] : "";
    int capacity = row[3] ? atoi(row[3]) : 0;

    Room room(id_room_in_dtb, id_theater_in_dtb, room_name, capacity);
    result.success = true;
    result.data = room;

    return result;
}