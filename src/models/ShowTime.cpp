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
    std::cout << std::left
              << std::setw(12) << "Room ID"
              << std::setw(12) << "Theater ID"
              << std::setw(25) << "Show Time"
              << std::setw(10) << "Movie ID"
              << "\n";

    std::cout << std::string(12 + 12 + 25 + 10, '-') << "\n";

    for (const auto& showtime : showtimes) {
        std::cout << std::left
                  << std::setw(12) << showtime.getRoomId()
                  << std::setw(12) << showtime.getTheaterId()
                  << std::setw(25) << showtime.getShowTime()
                  << std::setw(10) << showtime.getMovieId()
                  << "\n";
    }
}