#include "../../include/repositories/MovieRepository.h"

Result<vector<Movie>> MovieRepository::findAll(){
    Result<vector<Movie>> result;
    //Thuc hien truy van
    string query = "SELECT * FROM Movie";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    /*Neu thanh cong, lay ket qua
    Tao mot vector de chua danh sach phim*/
    vector<Movie> movies;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    /*Duyet qua tung dong ket qua
    Lay thong tin phim tu tung dong
    Tao mot doi tuong Movie va dua vao vector movies*/
    while ((row = mysql_fetch_row(res))) {
        int id_movie = row[0] ? atoi(row[0]) : 0;
        string title = row[1] ? row[1] : "";
        string genre = row[2] ? row[2] : "";
        string description = row[3] ? row[3] : "";
        int duration = row[4] ? atoi(row[4]) : 0;
        float rating = row[5] ? atof(row[5]) : 0.0f;
        string poster_path = row[6] ? row[6] : "";

        Movie movie(id_movie, title, genre, description, duration, rating, poster_path);
        movies.push_back(movie);
    }

    result.success = true;
    result.data = movies;
    return result;
}
//Get movie by id
Result<Movie> MovieRepository::findById(int id_movie){
    //Thuc hien truy van
    string query = "SELECT * FROM Movie WHERE movieID = " + std::to_string(id_movie);
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    Result<Movie> result;
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row = mysql_fetch_row(res);
    //Neu khong co ket qua, tra ve ket qua that bai
    if(!row){
        result.success = false;
        result.error_message = "Movie not found";
        return result;
    }
    //Neu co ket qua, lay thong tin phim
    Movie movie(
        id_movie,
        row[1] ? row[1] : "",
        row[2] ? row[2] : "",
        row[3] ? row[3] : "",
        row[4] ? atoi(row[4]) : 0,
        row[5] ? atof(row[5]) : 0.0f,
        row[6] ? row[6] : ""
    );
    //Tao doi tuong Movie va dua vao result
    result.success = true;
    result.data = movie;
    return result;
}
Result<vector<Movie>> MovieRepository::findByGenre(string genre){
    Result<vector<Movie>> result;
    //Thuc hien truy van
    std::string query = "SELECT * FROM Movie WHERE genre LIKE '" + genre + "%' COLLATE utf8mb4_general_ci";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    /*Neu thanh cong, lay ket qua
    Tao mot vector de chua danh sach phim*/
    vector<Movie> movies;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    /*Duyet qua tung dong ket qua
    Lay thong tin phim tu tung dong
    Tao mot doi tuong Movie va dua vao vector movies*/
    while ((row = mysql_fetch_row(res))) {
        int id_movie = row[0] ? atoi(row[0]) : 0;
        string title = row[1] ? row[1] : "";
        string genre = row[2] ? row[2] : "";
        string description = row[3] ? row[3] : "";
        int duration = row[4] ? atoi(row[4]) : 0;
        float rating = row[5] ? atof(row[5]) : 0.0f;
        string poster_path = row[6] ? row[6] : "";

        Movie movie(id_movie, title, genre, description, duration, rating, poster_path);
        movies.push_back(movie);
    }

    result.success = true;
    result.data = movies;
    return result;
}
//Get movie by name
Result<vector<Movie>> MovieRepository::findByName(string name){
    Result<vector<Movie>> result;
    //Thuc hien truy van
    std::string query = "SELECT * FROM Movie WHERE title LIKE '" + name + "%' COLLATE utf8mb4_general_ci";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    /*Kiem tra ket qua truy van
    Neu khong thanh cong, tra ve ket qua that bai*/
    if (!query_result.success) {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
    /*Neu thanh cong, lay ket qua
    Tao mot vector de chua danh sach phim*/
    vector<Movie> movies;
    MYSQL_RES *res = query_result.result.get();
    MYSQL_ROW row;
    /*Duyet qua tung dong ket qua
    Lay thong tin phim tu tung dong
    Tao mot doi tuong Movie va dua vao vector movies*/
    while ((row = mysql_fetch_row(res))) {
        int id_movie = row[0] ? atoi(row[0]) : 0;
        string title = row[1] ? row[1] : "";
        string genre = row[2] ? row[2] : "";
        string description = row[3] ? row[3] : "";
        int duration = row[4] ? atoi(row[4]) : 0;
        float rating = row[5] ? atof(row[5]) : 0.0f;
        string poster_path = row[6] ? row[6] : "";

        Movie movie(id_movie, title, genre, description, duration, rating, poster_path);
        movies.push_back(movie);
    }

    result.success = true;
    result.data = movies;
    return result;
}
//Add movie
Result<int> MovieRepository::create(const Movie& movie){
    //Thuc hien truy van
    Result<int> result;
    string query = "INSERT INTO Movie (title, genre, description, duration, rating, posterPath) VALUES ('" +
        movie.getMovieTitle() + "', '" +
        movie.getMovieGenre() + "', '" +
        movie.getMovieDescription() + "', " +
        std::to_string(movie.getMovieDuration()) + ", " +
        std::to_string(movie.getMovieRating()) + ", '" +
        movie.getMoviePosterPath() + "')";
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
        result.data = true;
    } else {
        result.success = false;
        result.error_message = "Failed to create movie";
    }
    return result;
}
//Update movie
Result<bool> MovieRepository::update(const Movie& movie){
    //Thuc hien truy van
    Result<bool> result;
    string query = "UPDATE Movie SET "
                   "title = '" + movie.getMovieTitle() + "', "
                   "genre = '" + movie.getMovieGenre() + "', "
                   "description = '" + movie.getMovieDescription() + "', "
                   "duration = " + std::to_string(movie.getMovieDuration()) + ", "
                   "rating = " + std::to_string(movie.getMovieRating()) + ", "
                   "posterPath = '" + movie.getMoviePosterPath() + "' "
                   "WHERE MovieID = " + std::to_string(movie.getMovieId());

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
        result.data = true;
    } else {
        result.success = false;
        result.error_message = "Failed to update movie";
    }
    return result;
}
//Delete movie
Result<bool> MovieRepository::remove(int id_movie){
    //Thuc hien truy van
    Result<bool> result;
    string query = "DELETE FROM Movie WHERE movieID = " + std::to_string(id_movie);
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
        result.data = true;
    } else {
        result.success = false;
        result.error_message = "Failed to delete movie";
    }
    return result;
}