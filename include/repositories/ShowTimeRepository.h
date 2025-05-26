/**
 * @file ShowTimeRepository.h
 * @brief Declares the ShowTimeRepository class for managing ShowTime data in the database.
 */

#ifndef SHOWTIMEREPOSITORY_H
#define SHOWTIMEREPOSITORY_H

#include "../../include/models/ShowTime.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class ShowTimeRepository
 * @brief Provides methods to interact with ShowTime data in the database.
 *
 * Inherits from IRepository<ShowTime> and implements CRUD operations and search functions for showtimes.
 */
class ShowTimeRepository: public IRepository<ShowTime> {
    public:
    /**
     * @brief Find all showtimes by movie ID.
     * @param id Movie ID
     * @return Result containing a vector of ShowTime objects.
     */
    Result<vector<ShowTime>> findShowTimeByMovieId(int id);

    /**
     * @brief Find all showtimes by theater ID.
     * @param id Theater ID
     * @return Result containing a vector of ShowTime objects.
     */
    Result<vector<ShowTime>> findShowTimeByTheaterId(int id);

    /**
     * @brief Find a specific showtime by ID and showtime string.
     * @param id ShowTime ID
     * @param showtime Show time string
     * @return Result containing the ShowTime object.
     */
    Result<ShowTime> findExactlyShowTime(int id, string showtime);

    /**
     * @brief Add a new showtime to the database.
     * @param showtime ShowTime object to add
     * @return Result containing the new showtime's ID.
     */
    Result<int> create(const ShowTime& showtime) override;

    /**
     * @brief Update an existing showtime in the database.
     * @param showtime ShowTime object with updated data
     * @return Result indicating success or failure.
     */
    Result<bool> update(const ShowTime& showtime) override;

    /**
     * @brief Remove a showtime from the database.
     * @param showtime ShowTime object to remove
     * @return Result indicating success or failure.
     */
    Result<bool> remove(const ShowTime& showtime);
};
#endif