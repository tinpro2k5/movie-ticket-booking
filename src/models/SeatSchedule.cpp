#include "../../include/models/SeatSchedule.h"

SeatSchedule::SeatSchedule(){
    _id_room = 0;
    _id_theater = 0;
    _seat_number = "";
    _show_time = "";
    _id_ticket = 0;
}

SeatSchedule::~SeatSchedule(){
    // Destructor
}

SeatSchedule::SeatSchedule(int id_room, int id_theater, string seat_number, string show_time, int id_ticket){
    _id_room = id_room;
    _id_theater = id_theater;
    _seat_number = seat_number;
    _show_time = show_time;
    _id_ticket = id_ticket;
}

// Getter methods
int SeatSchedule::getRoomId() const {
    return _id_room;
}
int SeatSchedule::getTheaterId() const {
    return _id_theater;
}
string SeatSchedule::getSeatNumber() const {
    return _seat_number;
}
string SeatSchedule::getShowTime() const {
    return _show_time;
}
int SeatSchedule::getTicketId() const {
    return _id_ticket;
}
// Setter methods
void SeatSchedule::setRoomId(const int& id_room) {
    _id_room = id_room;
}
void SeatSchedule::setTheaterId(const int& id_theater) {
    _id_theater = id_theater;
}
void SeatSchedule::setSeatNumber(const string& seat_number){
    _seat_number = seat_number;
}
void SeatSchedule::setShowTime(const string& show_time) {
    _show_time = show_time;
}
void SeatSchedule::setTicketId(const int& id_ticket){
    _id_ticket = id_ticket;
}
