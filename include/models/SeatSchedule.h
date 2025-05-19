#ifndef SEATSCHEDULE_H
#define SEATSCHEDULE_H

#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/models/Seat.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

class SeatSchedule{
    private:
    int _id_room;
    int _id_theater;
    string _seat_number;
    string _show_time;
    int _id_ticket;
    public:
    SeatSchedule();
    ~SeatSchedule();
    SeatSchedule(int id_room, int id_theater, string seat_number, string show_time, int id_ticket);
    //getter
    int getRoomId() const;
    int getTheaterId() const;
    string getSeatNumber() const;
    string getShowTime() const;
    int getTicketId() const;
    //setter
    void setRoomId(const int& id_room);
    void setTheaterId(const int& id_theater);
    void setSeatNumber(const string& seat_number);
    void setShowTime(const string& show_time);
    void setTicketId(const int& id_ticket);
};


#endif