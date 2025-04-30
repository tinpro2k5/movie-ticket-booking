#include "../../include/repositories/ShowTimeRepository.h"

Result<vector<ShowTime>> ShowTimeRepository::findShowTimeByMovieId(int id) {
    Result<vector<ShowTime>> result;
    string query = "SELECT * FROM Showtime WHERE movieID =" + std::to_string(id) + ";";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    vector<ShowTime> showtimes;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res))) {
        int id_room = std::atoi(row[0]);
        int id_theater = std::atoi(row[1]);
        string show_time = row[2];
        int id_movie = std::atoi(row[3]);
        ShowTime temp(id_room, id_theater, show_time, id_movie);
        // Tạo một đối tượng ShowTime và thêm vào danh sách
        showtimes.push_back(temp);
    }
    result.success = true;
    result.data = showtimes;
    return result;
}

Result<vector<ShowTime>> ShowTimeRepository::findShowTimeByTheaterId(int id) {
    Result<vector<ShowTime>> result;
    string query = "SELECT * FROM Showtime WHERE theaterID =" + std::to_string(id) + ";";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    vector<ShowTime> showtimes;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res))) {
        int id_room = std::stoi(row[0]);
        int id_theater = std::stoi(row[1]);
        string show_time = row[2];
        int id_movie = std::stoi(row[3]);

        // Tạo một đối tượng ShowTime và thêm vào danh sách
        showtimes.push_back(ShowTime(id_room, id_theater, show_time, id_movie));
    }
    result.success = true;
    result.data = showtimes;
    return result;
}

Result<bool> ShowTimeRepository::add(const ShowTime& showtime) {
    Result<bool> result;
    string query = "INSERT INTO Showtime (roomID, theaterID, showDateTime, movieID) VALUES (" +
                   std::to_string(showtime.getRoomId()) + ", " +
                   std::to_string(showtime.getTheaterId()) + ", '" +
                   showtime.getShowTime() + "', " +
                   std::to_string(showtime.getMovieId()) + ");";
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
        result.error_message = "Failed to add showtime";
        result.data = false;
    }
    return result;
}

Result<bool> ShowTimeRepository::update(const ShowTime& showtime) {
    Result<bool> result;
    string query = "UPDATE Showtime SET roomID = " + std::to_string(showtime.getRoomId()) +
                   ", theaterID = " + std::to_string(showtime.getTheaterId()) +
                   ", showDateTime = '" + showtime.getShowTime() +
                   "', movieID = " + std::to_string(showtime.getMovieId()) +
                   " WHERE roomID = " + std::to_string(showtime.getRoomId()) + ";";
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
        result.error_message = "Failed to update showtime";
        result.data = false;
    }
    return result;
}