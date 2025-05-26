/**
 * @file Movie.h
 * @brief Defines the Movie class and related functions for movie management.
 */

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <memory.h>
#include <exception>
#include <string>
#include <cstdlib>
#include <mysql/mysql.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "../utils/CultureFormatter.h"
using std::string, std::ostream, std::cout, std::endl, std::setw, std::left, std::vector;

/**
 * @class Movie
 * @brief Represents a movie in the system.
 *
 * The Movie class stores information about a movie, such as its ID, title, genre, description, duration, rating, poster path, and price.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class Movie {
 *   - int _id_movie
 *   - string _title
 *   - string _genre
 *   - string _description
 *   - int _duration
 *   - float _rating
 *   - string _poster_path
 *   - int _price
 *   + Movie()
 *   + ~Movie()
 *   + Movie(...)
 *   + getMovieId() : int
 *   + getMovieTitle() : string
 *   + getMovieGenre() : string
 *   + getMovieDescription() : string
 *   + getMovieDuration() : int
 *   + getMovieRating() : float
 *   + getMoviePosterPath() : string
 *   + getPrice() : int
 *   + setMovieId(const int&)
 *   + setMovieTitle(const string&)
 *   + setMovieGenre(const string&)
 *   + setMovieDescription(const string&)
 *   + setMovieDuration(const int&)
 *   + setMovieRating(const float&)
 *   + setMoviePosterPath(const string&)
 *   + setPrice(const int&)
 * }
 * @endverbatim
 */
class Movie{
    private:
    int _id_movie;           /**< Movie ID */
    string _title;           /**< Movie title */
    string _genre;           /**< Movie genre */
    string _description;     /**< Movie description */
    int _duration;           /**< Movie duration in minutes */
    float _rating;           /**< Movie rating */
    string _poster_path;     /**< Path to movie poster */
    int _price;              /**< Ticket price */
    public:
    /**
     * @brief Default constructor.
     */
    Movie();

    /**
     * @brief Destructor.
     */
    ~Movie();

    /**
     * @brief Parameterized constructor.
     * @param id_movie Movie ID
     * @param title Movie title
     * @param genre Movie genre
     * @param description Movie description
     * @param duration Movie duration in minutes
     * @param rating Movie rating
     * @param poster_path Path to movie poster
     * @param price Ticket price
     */
    Movie(const int& id_movie, const string& title, const string& genre, const string& description, const int& duration, const float& rating, const string& poster_path, const int& price);

    //getter
    /**
     * @brief Get the movie ID.
     * @return Movie ID
     */
    int getMovieId() const;

    /**
     * @brief Get the movie title.
     * @return Movie title
     */
    string getMovieTitle() const;

    /**
     * @brief Get the movie genre.
     * @return Movie genre
     */
    string getMovieGenre() const;

    /**
     * @brief Get the movie description.
     * @return Movie description
     */
    string getMovieDescription() const;

    /**
     * @brief Get the movie duration.
     * @return Movie duration in minutes
     */
    int getMovieDuration() const;

    /**
     * @brief Get the movie rating.
     * @return Movie rating
     */
    float getMovieRating() const;

    /**
     * @brief Get the movie poster path.
     * @return Path to movie poster
     */
    string getMoviePosterPath() const;

    /**
     * @brief Get the ticket price.
     * @return Ticket price
     */
    int getPrice() const;

    //setter
    /**
     * @brief Set the movie ID.
     * @param id_movie Movie ID
     */
    void setMovieId(const int& id_movie);

    /**
     * @brief Set the movie title.
     * @param title Movie title
     */
    void setMovieTitle(const string& title);

    /**
     * @brief Set the movie genre.
     * @param genre Movie genre
     */
    void setMovieGenre(const string& genre);

    /**
     * @brief Set the movie description.
     * @param description Movie description
     */
    void setMovieDescription(const string& description);

    /**
     * @brief Set the movie duration.
     * @param duration Movie duration in minutes
     */
    void setMovieDuration(const int& duration);

    /**
     * @brief Set the movie rating.
     * @param rating Movie rating
     */
    void setMovieRating(const float& rating);

    /**
     * @brief Set the movie poster path.
     * @param poster_path Path to movie poster
     */
    void setMoviePosterPath(const string& poster_path);

    /**
     * @brief Set the ticket price.
     * @param price Ticket price
     */
    void setPrice(const int& price);
    //
};

/**
 * @brief Print a table of movies.
 * @param movies Vector of Movie objects
 */
void printMoviesTable(const std::vector<Movie>& movies);

/**
 * @brief Print a vector of movies.
 * @param movies Vector of Movie objects
 */
void printMovieVector(const std::vector<Movie>& movies);

#endif