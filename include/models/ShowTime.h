/**
 * @file ShowTime.h
 * @brief Defines the ShowTime class and related functions for showtime management.
 */

#ifndef SHOWTIME_H
#define SHOWTIME_H
#include "../../include/models/Movie.h"
#include "../../include/models/MovieTheater.h"
#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"

/**
 * @class ShowTime
 * @brief Represents a showtime in a movie theater room.
 *
 * The ShowTime class stores information about a showtime, such as its room ID, theater ID, show time, and movie ID.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class ShowTime {
 *   - int _id_room
 *   - int _id_theater
 *   - string _show_time
 *   - int _id_movie
 *   + ShowTime()
 *   + ~ShowTime()
 *   + ShowTime(...)
 *   + getRoomId() : int
 *   + getTheaterId() : int
 *   + getShowTime() : string
 *   + getMovieId() : int
 *   + setRoomId(const int&)
 *   + setTheaterId(const int&)
 *   + setShowTime(const string&)
 *   + setMovieId(const int&)
 * }
 * @endverbatim
 */
class ShowTime{
    private:
    int _id_room;        /**< Room ID */
    int _id_theater;     /**< Theater ID */
    string _show_time;   /**< Show time */
    int _id_movie;       /**< Movie ID */
    public:
    /**
     * @brief Default constructor.
     */
    ShowTime();

    /**
     * @brief Destructor.
     */
    ~ShowTime();

    /**
     * @brief Parameterized constructor.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param show_time Show time
     * @param id_movie Movie ID
     */
    ShowTime(int id_room, int id_theater, string show_time, int id_movie);

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
     * @brief Get the show time.
     * @return Show time
     */
    string getShowTime() const;

    /**
     * @brief Get the movie ID.
     * @return Movie ID
     */
    int getMovieId() const;

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
     * @brief Set the show time.
     * @param show_time Show time
     */
    void setShowTime(const string& show_time);

    /**
     * @brief Set the movie ID.
     * @param id_movie Movie ID
     */
    void setMovieId(const int& id_movie);
};

/**
 * @brief Print a table of showtimes.
 * @param showtimes Vector of ShowTime objects
 */
void printShowtimeTable(const std::vector<ShowTime>& showtimes);

#endif