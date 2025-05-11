#include "../../include/repositories/RoomRepository.h"

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
Result<vector<Room>> RoomRepository::findAll(){
    Result<vector<Room>> result;
    std::string query = "SELECT * FROM Room";
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
Result<int> RoomRepository::create(const Room& room){
    Result<int> result;
    std::string query = "INSERT INTO Room (roomID, theaterID, name, capacity) VALUES (" +
                        std::to_string(room.getRoomId()) + ", " +
                        std::to_string(room.getTheaterId()) + ", '" +
                        room.getRoomName() + "', " +
                        std::to_string(room.getRoomCapacity()) + ")";

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);

    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    if (query_result.affected_rows > 0) {
            result.success = true;
            QueryResult id_result = DatabaseManager::getInstance()->executeQuery("SELECT LAST_INSERT_ID() AS id");
            if (id_result.success && id_result.result) {
                MYSQL_ROW row = mysql_fetch_row(id_result.result.get());
                if (row && row[0]) {
                    result.data = std::stoi(row[0]); // ép kiểu chuỗi sang số
                } else {
                    result.success = false;
                    result.error_message = "Không đọc được roomID.";
                }
            } else {
                result.success = false;
                result.error_message = "Không thể thực hiện truy vấn lấy roomID.";
            }
        } else {
            result.success = false;
            result.error_message = "Failed to room";
        }
    return result;
}

Result<bool> RoomRepository::update(const Room& room) {
    Result<bool> result;
    std::string query = "UPDATE Room SET theaterID = " + std::to_string(room.getTheaterId()) +
                        ", name = '" + room.getRoomName() +
                        "', capacity = " + std::to_string(room.getRoomCapacity()) +
                        " WHERE roomID = " + std::to_string(room.getRoomId()) + 
                        " AND theaterID = " + std::to_string(room.getTheaterId()) + ";";

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);

    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    if (query_result.affected_rows > 0) {
        result.success = true;
        result.data = true;
    } else {
        result.success = false;
        result.error_message = "Failed to update room";
    }
    return result;
}