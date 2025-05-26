/**
 * @file Seat.h
 * @brief Defines the Seat class and related functions for seat management.
 */

#ifndef SEAT_H
#define SEAT_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

/**
 * @class Seat
 * @brief Represents a seat in a movie theater room.
 *
 * The Seat class stores information about a seat, such as its room ID, theater ID, seat number, and VIP status.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class Seat {
 *   - int _id_room
 *   - int _id_theater
 *   - string _seat_number
 *   - bool _is_vip
 *   + Seat()
 *   + ~Seat()
 *   + Seat(...)
 *   + getRoomId() : int
 *   + getTheaterId() : int
 *   + getSeatNumber() : string
 *   + isVip() : bool
 *   + setRoomId(const int&)
 *   + setTheaterId(const int&)
 *   + setSeatNumber(const string&)
 *   + setVip(const bool&)
 * }
 * @endverbatim
 */
class Seat{
    private:
    int _id_room;           /**< Room ID */
    int _id_theater;        /**< Theater ID */
    string _seat_number;    /**< Seat number */
    bool _is_vip;           /**< VIP status */
    public:
    /**
     * @brief Default constructor.
     */
    Seat();

    /**
     * @brief Destructor.
     */
    ~Seat();

    /**
     * @brief Parameterized constructor.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @param is_vip VIP status
     */
    Seat(int id_room, int id_theater, string seat_number, bool is_vip);

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
     * @brief Check if the seat is VIP.
     * @return True if VIP, false otherwise
     */
    bool isVip() const;

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
     * @brief Set the VIP status.
     * @param is_vip VIP status
     */
    void setVip(const bool& is_vip);
};

#endif