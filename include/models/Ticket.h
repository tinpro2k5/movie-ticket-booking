/**
 * @file Ticket.h
 * @brief Defines the Ticket class and related functions for ticket management.
 */

#ifndef TICKET_H
#define TICKET_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/models/Seat.h"
#include "../../include/models/User.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

/**
 * @class Ticket
 * @brief Represents a ticket for a movie showtime.
 *
 * The Ticket class stores information about a ticket, such as its ID, user ID, room ID, theater ID, seat number, show time, price, booking time, and payment status.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class Ticket {
 *   - int _id_ticket
 *   - int _id_user
 *   - int _id_room
 *   - int _id_theater
 *   - string _seat_number
 *   - string _show_time
 *   - double _price
 *   - string _booking_time
 *   - bool _is_paid
 *   + Ticket()
 *   + ~Ticket()
 *   + Ticket(...)
 *   + getTicketId() : int
 *   + getUserId() : int
 *   + getRoomId() : int
 *   + getTheaterId() : int
 *   + getSeatNumber() : string
 *   + getShowTime() : string
 *   + getPrice() : double
 *   + getBookingTime() : string
 *   + isPaid() : bool
 *   + setTicketId(const int&)
 *   + setUserId(const int&)
 *   + setRoomId(const int&)
 *   + setTheaterId(const int&)
 *   + setSeatNumber(const string&)
 *   + setShowTime(const string&)
 *   + setPrice(const double&)
 *   + setBookingTime(const string&)
 *   + setPaid(const bool&)
 * }
 * @endverbatim
 */
class Ticket{
    private:
    int _id_ticket;         /**< Ticket ID */
    int _id_user;           /**< User ID */
    int _id_room;           /**< Room ID */
    int _id_theater;        /**< Theater ID */
    string _seat_number;    /**< Seat number */
    string _show_time;      /**< Show time */
    double _price;          /**< Ticket price */
    string _booking_time;   /**< Booking time */
    bool _is_paid;          /**< Payment status */
    public:
    /**
     * @brief Default constructor.
     */
    Ticket();

    /**
     * @brief Destructor.
     */
    ~Ticket();

    /**
     * @brief Parameterized constructor.
     * @param id_ticket Ticket ID
     * @param id_user User ID
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @param show_time Show time
     * @param price Ticket price
     * @param booking_time Booking time
     * @param is_paid Payment status
     */
    Ticket(int id_ticket, int id_user, int id_room, int id_theater, string seat_number, string show_time, double price, string booking_time, bool is_paid);

    //getter
    /**
     * @brief Get the ticket ID.
     * @return Ticket ID
     */
    int getTicketId() const;

    /**
     * @brief Get the user ID.
     * @return User ID
     */
    int getUserId() const;

    /**
     * @brief Get the room ID.
     * @return Room ID
     */
    int getRoomId() const;

    /**
     * @brief Get the theater ID.
     * @return Theater ID
     */
    int getTheaterId() const;

    /**
     * @brief Get the seat number.
     * @return Seat number
     */
    string getSeatNumber() const;

    /**
     * @brief Get the show time.
     * @return Show time
     */
    string getShowTime() const;

    /**
     * @brief Get the ticket price.
     * @return Ticket price
     */
    double getPrice() const;

    /**
     * @brief Get the booking time.
     * @return Booking time
     */
    string getBookingTime() const;

    /**
     * @brief Check if the ticket is paid.
     * @return True if paid, false otherwise
     */
    bool isPaid() const;

    //setter
    /**
     * @brief Set the ticket ID.
     * @param id_ticket Ticket ID
     */
    void setTicketId(const int& id_ticket);

    /**
     * @brief Set the user ID.
     * @param id_user User ID
     */
    void setUserId(const int& id_user);

    /**
     * @brief Set the room ID.
     * @param id_room Room ID
     */
    void setRoomId(const int& id_room);

    /**
     * @brief Set the theater ID.
     * @param id_theater Theater ID
     */
    void setTheaterId(const int& id_theater);

    /**
     * @brief Set the seat number.
     * @param seat_number Seat number
     */
    void setSeatNumber(const string& seat_number);

    /**
     * @brief Set the show time.
     * @param show_time Show time
     */
    void setShowTime(const string& show_time);

    /**
     * @brief Set the ticket price.
     * @param price Ticket price
     */
    void setPrice(const double& price);

    /**
     * @brief Set the booking time.
     * @param booking_time Booking time
     */
    void setBookingTime(const string& booking_time);

    /**
     * @brief Set the payment status.
     * @param is_paid Payment status
     */
    void setPaid(const bool& is_paid);
};

/**
 * @brief Print a table of tickets.
 * @param tickets Vector of Ticket objects
 */
void printTicketTable(const vector<Ticket>& tickets);

#endif