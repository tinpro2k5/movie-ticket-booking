/**
 * @file SeatSchedule.h
 * @brief Defines the SeatSchedule class and related functions for seat schedule management.
 */

#ifndef SEATSCHEDULE_H
#define SEATSCHEDULE_H

#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/models/Seat.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

/**
 * @class SeatSchedule
 * @brief Represents a seat schedule for a specific showtime in a movie theater room.
 *
 * The SeatSchedule class stores information about a seat's schedule, such as its room ID, theater ID, seat number, show time, and ticket ID.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class SeatSchedule {
 *   - int _id_room
 *   - int _id_theater
 *   - string _seat_number
 *   - string _show_time
 *   - int _id_ticket
 *   + SeatSchedule()
 *   + ~SeatSchedule()
 *   + SeatSchedule(...)
 *   + getRoomId() : int
 *   + getTheaterId() : int
 *   + getSeatNumber() : string
 *   + getShowTime() : string
 *   + getTicketId() : int
 *   + setRoomId(const int&)
 *   + setTheaterId(const int&)
 *   + setSeatNumber(const string&)
 *   + setShowTime(const string&)
 *   + setTicketId(const int&)
 * }
 * @endverbatim
 */
class SeatSchedule{
    private:
    int _id_room;           /**< Room ID */
    int _id_theater;        /**< Theater ID */
    string _seat_number;    /**< Seat number */
    string _show_time;      /**< Show time */
    int _id_ticket;         /**< Ticket ID */
    public:
    /**
     * @brief Default constructor.
     */
    SeatSchedule();

    /**
     * @brief Destructor.
     */
    ~SeatSchedule();

    /**
     * @brief Parameterized constructor.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @param show_time Show time
     * @param id_ticket Ticket ID
     */
    SeatSchedule(int id_room, int id_theater, string seat_number, string show_time, int id_ticket);

    //getter
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
     * @brief Get the ticket ID.
     * @return Ticket ID
     */
    int getTicketId() const;

    //setter
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
     * @brief Set the ticket ID.
     * @param id_ticket Ticket ID
     */
    void setTicketId(const int& id_ticket);
};

#endif