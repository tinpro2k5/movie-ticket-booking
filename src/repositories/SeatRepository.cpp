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

Result<int> SeatRepository::create(const Seat& seat){
    Result<int> result;
    string query = "INSERT INTO Seat (roomID, theaterID, seatNumber, isVip) VALUES (" +
                   std::to_string(seat.getRoomId()) + ", " +
                   std::to_string(seat.getTheaterId()) + ", '" +
                   seat.getSeatNumber() + "', " +
                   (seat.isVip() ? "TRUE" : "FALSE") + ")";
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
                result.error_message = "Không đọc được ban ghi moi.";
            }
        } else {
            result.success = false;
            result.error_message = "Không thể thực hiện truy vấn lấy ban ghi moi.";
        }
    } else {
            result.success = false;
            result.error_message = "Failed to seat create ";
    }
    return result;
}