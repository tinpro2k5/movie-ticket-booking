#ifndef SHOWTIME_H
#define SHOWTIME_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
class ShowTime{
    private:
    int _id_room;
    int _id_theater;
    string _show_time;
    int _id_movie;
    public:
    ShowTime();
    ~ShowTime();
    ShowTime(int id_room, int id_theater, string show_time, int id_movie);
    //getter
    int getRoomId() const;
    int getTheaterId() const;
    string getShowTime() const;
    int getMovieId() const;
    //setter
    void setRoomId(const int& id_room);
    void setTheaterId(const int& id_theater);
    void setShowTime(const string& show_time);
    void setMovieId(const int& id_movie);
};
void printShowtimeTable(const std::vector<ShowTime>& showtimes);
#endif