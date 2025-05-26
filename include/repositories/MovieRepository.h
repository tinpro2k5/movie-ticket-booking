/**
 * @file MovieRepository.h
 * @brief Declares the MovieRepository class for managing Movie data in the database.
 */

#ifndef MOVIEREPOSITORY_H
#define MOVIEREPOSITORY_H

#include "../../include/models/Movie.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class MovieRepository
 * @brief Provides methods to interact with Movie data in the database.
 *
 * Inherits from IRepository<Movie> and implements CRUD operations and search functions for movies.
 */
class MovieRepository: public IRepository<Movie> {
    public:
        /**
         * @brief Retrieve all movies from the database.
         * @return Result containing a vector of Movie objects.
         */
        Result<vector<Movie>> findAll();

        /**
         * @brief Find a movie by its ID.
         * @param id_movie Movie ID
         * @return Result containing the Movie object.
         */
        Result<Movie> findById(int id_movie);

        /**
         * @brief Find movies by genre.
         * @param genre Movie genre
         * @return Result containing a vector of Movie objects.
         */
        Result<vector<Movie>> findByGenre(string genre);

        /**
         * @brief Find movies by name.
         * @param name Movie name
         * @return Result containing a vector of Movie objects.
         */
        Result<vector<Movie>> findByName(string name);

        /**
         * @brief Add a new movie to the database.
         * @param movie Movie object to add
         * @return Result containing the new movie's ID.
         */
        Result<int> create(const Movie& movie) override;

        /**
         * @brief Update an existing movie in the database.
         * @param movie Movie object with updated data
         * @return Result indicating success or failure.
         */
        Result<bool> update(const Movie& movie) override;

        /**
         * @brief Remove a movie from the database by ID.
         * @param id_movie Movie ID
         * @return Result indicating success or failure.
         */
        Result<bool> remove(int id_movie) override;
};

#endif