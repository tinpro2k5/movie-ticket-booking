/**
 * @file SeatRepository.h
 * @brief Declares the SeatRepository class for managing Seat data in the database.
 */

#ifndef SEATREPOSITORY_H
#define SEATREPOSITORY_H
#include "../../include/models/Seat.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class SeatRepository
 * @brief Provides methods to interact with Seat data in the database.
 *
 * Inherits from IRepository<Seat> and implements CRUD operations and search functions for seats.
 */
class SeatRepository: public IRepository<Seat> {   
    public:
    /**
     * @brief Find all seats by room ID and theater ID.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @return Result containing a vector of Seat objects.
     */
    Result<vector<Seat>> findByRoomId(int id_room, int id_theater);

    /**
     * @brief Find a seat by room ID, theater ID, and seat number.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @return Result containing the Seat object.
     */
    Result<Seat> findById(int id_room, int id_theater, string seat_number);

    /**
     * @brief Check if a seat is VIP.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @return Result indicating if the seat is VIP.
     */
    Result<bool> checkVipSeat(int id_room, int id_theater, string seat_number);

    /**
     * @brief Add a new seat to the database.
     * @param seat Seat object to add
     * @return Result containing the new seat's ID.
     */
    Result<int> create(const Seat& seat) override;
};
#endif