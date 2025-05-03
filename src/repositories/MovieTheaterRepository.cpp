#include "../../include/repositories/MovieTheaterRepository.h"

Result<vector<MovieTheater>> MovieTheaterRepository::findAll(){
    Result<vector<MovieTheater>> result;
    //Thuc hien truy van
    string query = "SELECT * FROM Theater";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    /*Neu thanh cong, lay ket qua
    Tao mot vector de chua danh sach rap*/
    vector<MovieTheater> movie_theaters;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    /*Duyet qua tung dong ket qua
    Lay thong tin rap tu tung dong
    Tao mot doi tuong MovieTheater va dua vao vector movieTheaters*/
    while ((row = mysql_fetch_row(res))) {
        int id_theater = row[0] ? atoi(row[0]) : 0;
        string name = row[1] ? row[1] : "";
        string location = row[2] ? row[2] : "";

        MovieTheater movieTheater(id_theater, name, location);
        movie_theaters.push_back(movieTheater);
    }

    result.success = true;
    result.data = movie_theaters;
    return result;
}
Result<MovieTheater> MovieTheaterRepository::findById(int id_theater){
    Result<MovieTheater> result;
    //Thuc hien truy van
    string query = "SELECT * FROM Theater WHERE theaterID = " + std::to_string(id_theater);
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row = mysql_fetch_row(res);
    /*Kiem tra xem co ket qua hay khong
    Neu khong co, tra ve ket qua that bai*/
    if (!row) {
        result.success = false;
        result.error_message = "Movie theater not found";
        return result;
    }
    /*Lay thong tin rap tu dong ket qua
    Tao mot doi tuong MovieTheater va dua vao ket qua*/
    int id_theater_in_dtb = row[0] ? atoi(row[0]) : 0;
    string name = row[1] ? row[1] : "";
    string location = row[2] ? row[2] : "";

    MovieTheater movieTheater(id_theater_in_dtb, name, location);
    
    result.success = true;
    result.data = movieTheater;

    return result;
}
Result<bool> MovieTheaterRepository::insert(const MovieTheater& movie_theater){
    Result<bool> result;
    //Thuc hien truy van
    string query = "INSERT INTO Theater (theaterID, name, location) VALUES (" + std::to_string(movie_theater.getTheaterId()) + ", '" 
    + movie_theater.getTheaterName() + "', '" 
    + movie_theater.getTheaterLocation() + "')";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
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
        result.error_message = "Failed to add movie";
    }
    return result;
}
Result<bool> MovieTheaterRepository::update(const MovieTheater& movie_theater){
    Result<bool> result;
    //Thuc hien truy van
    string query = "UPDATE Theater SET name = '" + movie_theater.getTheaterName() + "', location = '" 
    + movie_theater.getTheaterLocation() + "' WHERE theaterID = " 
    + std::to_string(movie_theater.getTheaterId());
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
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
        result.error_message = "Failed to update movie theater";
    }
    return result;
}