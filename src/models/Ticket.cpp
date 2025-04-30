#include "../../include/models/Ticket.h"

Ticket::Ticket(){
    _id_ticket = 0;
    _id_user = 0;
    _id_room = 0;
    _id_theater = 0;
    _seat_number = "";
    _show_time = "";
    _price = 0.0;
    _booking_time = "";
    _is_paid = false;
}

Ticket::~Ticket(){
    // Destructor
}
Ticket::Ticket(int id_ticket, int id_user, int id_room, int id_theater, string seat_number, string show_time, double price, string booking_time, bool is_paid){
    _id_ticket = id_ticket;
    _id_user = id_user;
    _id_room = id_room;
    _id_theater = id_theater;
    _seat_number = seat_number;
    _show_time = show_time;
    _price = price;
    _booking_time = booking_time;
    _is_paid = is_paid;
}
//getter
int Ticket::getTicketId() const{
    return _id_ticket;
}
int Ticket::getUserId() const{
    return _id_user;
}
int Ticket::getRoomId() const{
    return _id_room;
}
int Ticket::getTheaterId() const{
    return _id_theater;
}
string Ticket::getSeatNumber() const{
    return _seat_number;
}
string Ticket::getShowTime() const{
    return _show_time;
}
double Ticket::getPrice() const{
    return _price;
}
string Ticket::getBookingTime() const{
    return _booking_time;
}
bool Ticket::isPaid() const{
    return _is_paid;
}
//setter
void Ticket::setTicketId(int id_ticket){
    _id_ticket = id_ticket;
}
void Ticket::setUserId(int id_user){
    _id_user = id_user;
}
void Ticket::setRoomId(int id_room){
    _id_room = id_room;
}
void Ticket::setTheaterId(int id_theater){
    _id_theater = id_theater;
}
void Ticket::setSeatNumber(string seat_number){
    _seat_number = seat_number;
}
void Ticket::setShowTime(string show_time){
    _show_time = show_time;
}
void Ticket::setPrice(double price){
    _price = price;
}
void Ticket::setBookingTime(string booking_time){
    _booking_time = booking_time;
}
void Ticket::setPaid(bool is_paid){
    _is_paid = is_paid;
}
