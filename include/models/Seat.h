#ifndef SEAT_H
#define SEAT_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"


class Seat{
    private:
    int _id_room;
    int _id_theater;
    string _seat_number;
    bool _is_vip;
    public:
    Seat();
    ~Seat();
    Seat(int id_room, int id_theater, string seat_number, bool is_vip);
    //getter
    int getRoomId() const;
    int getTheaterId() const;  
    string getSeatNumber() const;
    bool isVip() const;
    //setter
    void setRoomId(const int& id_room);
    void setTheaterId(const int& id_theater);
    void setSeatNumber(const string& seat_number);
    void setVip(const bool& is_vip);
};
#endif