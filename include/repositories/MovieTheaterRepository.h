/**
 * @file MovieTheaterRepository.h
 * @brief Declares the MovieTheaterRepository class for managing MovieTheater data in the database.
 */

#ifndef MOVIETHEATERREPOSITORIES_H
#define MOVIETHEATERREPOSITORIES_H

#include "../../include/models/MovieTheater.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"   
#include "../../include/repositories/IRepository.h"

/**
 * @class MovieTheaterRepository
 * @brief Provides methods to interact with MovieTheater data in the database.
 *
 * Inherits from IRepository<MovieTheater> and implements CRUD operations for movie theaters.
 */
class MovieTheaterRepository: public IRepository<MovieTheater> {
    public:
    /**
     * @brief Retrieve all movie theaters from the database.
     * @return Result containing a vector of MovieTheater objects.
     */
    Result<vector<MovieTheater>> findAll();

    /**
     * @brief Find a movie theater by its ID.
     * @param id_theater Theater ID
     * @return Result containing the MovieTheater object.
     */
    Result<MovieTheater> findById(int id_theater);

    /**
     * @brief Add a new movie theater to the database.
     * @param movie_theater MovieTheater object to add
     * @return Result containing the new theater's ID.
     */
    Result<int> create(const MovieTheater& movie_theater) override;

    /**
     * @brief Update an existing movie theater in the database.
     * @param movie_theater MovieTheater object with updated data
     * @return Result indicating success or failure.
     */
    Result<bool> update(const MovieTheater& movie_theater) override;
};
#endif