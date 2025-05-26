/**
 * @file MovieTheater.h
 * @brief Defines the MovieTheater class and related functions for theater management.
 */

#ifndef MOVIE_THEATER_H
#define MOVIE_THEATER_H
#include "./Movie.h"

/**
 * @class MovieTheater
 * @brief Represents a movie theater in the system.
 *
 * The MovieTheater class stores information about a theater, such as its ID, name, and location.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class MovieTheater {
 *   - int _id_theater
 *   - string _name
 *   - string _location
 *   + MovieTheater()
 *   + ~MovieTheater()
 *   + MovieTheater(...)
 *   + getTheaterId() : int
 *   + getTheaterName() : string
 *   + getTheaterLocation() : string
 *   + setTheaterId(const int&)
 *   + setTheaterName(const string&)
 *   + setTheaterLocation(const string&)
 * }
 * @endverbatim
 */
class MovieTheater {
    private:
    int _id_theater;      /**< Theater ID */
    string _name;         /**< Theater name */
    string _location;     /**< Theater location */
    public:
    /**
     * @brief Default constructor.
     */
    MovieTheater();

    /**
     * @brief Destructor.
     */
    ~MovieTheater();

    /**
     * @brief Parameterized constructor.
     * @param id_theater Theater ID
     * @param name Theater name
     * @param location Theater location
     */
    MovieTheater(int id_theater, string name, string location);

    //getter
    /**
     * @brief Get the theater ID.
     * @return Theater ID
     */
    int getTheaterId() const;

    /**
     * @brief Get the theater name.
     * @return Theater name
     */
    string getTheaterName() const;

    /**
     * @brief Get the theater location.
     * @return Theater location
     */
    string getTheaterLocation() const;

    //setter
    /**
     * @brief Set the theater ID.
     * @param id_theater Theater ID
     */
    void setTheaterId(const int& id_theater);

    /**
     * @brief Set the theater name.
     * @param name Theater name
     */
    void setTheaterName(const string& name);

    /**
     * @brief Set the theater location.
     * @param location Theater location
     */
    void setTheaterLocation(const string& location);
    //

};

/**
 * @brief Print a table of movie theaters.
 * @param theaters Vector of MovieTheater objects
 */
void printTheaterTable(const vector<MovieTheater>& theaters);

#endif