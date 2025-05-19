#ifndef TICKET_H
#define TICKET_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/models/Seat.h"
#include "../../include/models/User.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

class Ticket{
    private:
    int _id_ticket;
    int _id_user;
    int _id_room;
    int _id_theater;
    string _seat_number;
    string _show_time;
    double _price;
    string _booking_time;
    bool _is_paid;
    public:
    Ticket();
    ~Ticket();

    Ticket(int id_ticket, int id_user, int id_room, int id_theater, string seat_number, string show_time, double price, string booking_time, bool is_paid);
    //getter
    int getTicketId() const;
    int getUserId() const;
    int getRoomId() const;
    int getTheaterId() const;
    string getSeatNumber() const;
    string getShowTime() const;
    double getPrice() const;
    string getBookingTime() const;
    bool isPaid() const;
    //setter
    void setTicketId(const int& id_ticket);
    void setUserId(const int& id_user);
    void setRoomId(const int& id_room);
    void setTheaterId(const int& id_theater);
    void setSeatNumber(const string& seat_number);
    void setShowTime(const string& show_time);
    void setPrice(const double& price);
    void setBookingTime(const string& booking_time);
    void setPaid(const bool& is_paid);
};
void printTicketTable(const vector<Ticket>& tickets);
#endif