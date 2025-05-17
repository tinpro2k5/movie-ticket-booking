#include "../../include/models/ShowTime.h"

ShowTime::ShowTime() {
    _id_room = 0;
    _id_theater = 0;
    _show_time = "";
    _id_movie = 0;
}
ShowTime::~ShowTime() {
}
ShowTime::ShowTime(int id_room, int id_theater, string show_time, int id_movie) {
    _id_room = id_room;
    _id_theater = id_theater;
    _show_time = show_time;
    _id_movie = id_movie;
}
//getter
int ShowTime::getRoomId() const {
    return _id_room;
}
int ShowTime::getTheaterId() const {
    return _id_theater;
}
string ShowTime::getShowTime() const {
    return _show_time;
}
int ShowTime::getMovieId() const {
    return _id_movie;
}
//setter
void ShowTime::setRoomId(int id_room) {
    _id_room = id_room;
}
void ShowTime::setTheaterId(int id_theater) {
    _id_theater = id_theater;
}
void ShowTime::setShowTime(string show_time) {
    _show_time = show_time;
}
void ShowTime::setMovieId(int id_movie) {
    _id_movie = id_movie;
}

void printShowtimeTable(const std::vector<ShowTime>& showtimes) {
    std::cout << "| " << std::left
              << std::setw(15) << "Room ID" << " | "
              << std::setw(15) << "Theater ID" << " | "
              << std::setw(30) << "Show Time" << " | "
              << std::setw(12) << "Movie ID" << " |"
              << "\n";

    // In dòng kẻ ngăn cách
    std::cout << "|" << std::string(17, '-') << "|"
              << std::string(17, '-') << "|"
              << std::string(32, '-') << "|"
              << std::string(14, '-') << "|" << "\n";

    for (const auto& showtime : showtimes) {
        std::cout << "| " << std::left
                  << std::setw(15) << showtime.getRoomId() << " | "
                  << std::setw(15) << showtime.getTheaterId() << " | "
                  << std::setw(30) << showtime.getShowTime() << " | "
                  << std::setw(12) << showtime.getMovieId() << " |"
                  << "\n";
    }
}