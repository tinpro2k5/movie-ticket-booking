/**
 * @file SeatScheduleRepository.h
 * @brief Declares the SeatScheduleRepository class for managing SeatSchedule data in the database.
 */

#ifndef SEATSCHEDULEREPOSITORY_H
#define SEATSCHEDULEREPOSITORY_H

#include "../../include/models/SeatSchedule.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class SeatScheduleRepository
 * @brief Provides methods to interact with SeatSchedule data in the database.
 *
 * Inherits from IRepository<SeatSchedule> and implements CRUD operations and search functions for seat schedules.
 */
class SeatScheduleRepository: public IRepository<SeatSchedule> {
    public:
    /**
     * @brief Find all available seats for a specific showtime.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param show_time Show time
     * @return Result containing a vector of available SeatSchedule objects.
     */
    Result<vector<SeatSchedule>> findAvailableSeats(int id_room, int id_theater, string show_time);

    /**
     * @brief Find a seat by room ID, theater ID, seat number, and show time.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param seat_number Seat number
     * @param show_time Show time
     * @return Result indicating if the seat exists for the given showtime.
     */
    Result<bool> findSeatById(int id_room, int id_theater, string seat_number, string show_time);

    /**
     * @brief Update a seat schedule in the database.
     * @param ss SeatSchedule object with updated data
     * @return Result indicating success or failure.
     */
    Result<bool> update(const SeatSchedule& ss) override;

    /**
     * @brief Add a new seat schedule to the database.
     * @param ss SeatSchedule object to add
     * @return Result containing the new seat schedule's ID.
     */
    Result<int> create(const SeatSchedule& ss) override;
};
#endif