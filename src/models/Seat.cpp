#include "../../include/models/Seat.h"

Seat::Seat() {
    _id_room = 0;
    _id_theater = 0;
    _seat_number = "";
    _is_vip = false;
}

Seat::~Seat() {
}

Seat::Seat(int id_room, int id_theater, string seat_number, bool is_vip) {
    _id_room = id_room;
    _id_theater = id_theater;
    _seat_number = seat_number;
    _is_vip = is_vip;
}

int Seat::getRoomId() const {
    return _id_room;
}

int Seat::getTheaterId() const {
    return _id_theater;
}

string Seat::getSeatNumber() const {
    return _seat_number;
}

bool Seat::isVip() const {
    return _is_vip;
}

void Seat::setRoomId(int id_room) {
    _id_room = id_room;
}

void Seat::setTheaterId(int id_theater) {
    _id_theater = id_theater;
}

void Seat::setSeatNumber(string seat_number) {
    _seat_number = seat_number;
}

void Seat::setVip(bool is_vip) {
    _is_vip = is_vip;
}
