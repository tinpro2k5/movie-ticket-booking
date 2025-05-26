/**
 * @file Room.h
 * @brief Defines the Room class and related functions for room management.
 */

#ifndef ROOM_H
#define ROOM_H
#include "../../include/models/Movie.h"

/**
 * @class Room
 * @brief Represents a room in a movie theater.
 *
 * The Room class stores information about a room, such as its ID, the theater it belongs to, its name, and its capacity.
 *
 * Example class diagram (PlantUML syntax):
 * @verbatim
 * class Room {
 *   - int _id_room
 *   - int _id_theater
 *   - string _room_name
 *   - int _capacity
 *   + Room()
 *   + ~Room()
 *   + Room(...)
 *   + getRoomId() : int
 *   + getTheaterId() : int
 *   + getRoomName() : string
 *   + getRoomCapacity() : int
 *   + setRoomId(const int&)
 *   + setTheaterId(const int&)
 *   + setRoomName(const string&)
 *   + setRoomCapacity(const int&)
 * }
 * @endverbatim
 */
class Room {
    private:
    int _id_room;        /**< Room ID */
    int _id_theater;     /**< Theater ID */
    string _room_name;   /**< Room name */
    int _capacity;       /**< Room capacity */
    public:
    /**
     * @brief Default constructor.
     */
    Room();

    /**
     * @brief Destructor.
     */
    ~Room();

    /**
     * @brief Parameterized constructor.
     * @param id_room Room ID
     * @param id_theater Theater ID
     * @param room_name Room name
     * @param capacity Room capacity
     */
    Room(int id_room, int id_theater, string room_name, int capacity);

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
     * @brief Get the room name.
     * @return Room name
     */
    string getRoomName() const;

    /**
     * @brief Get the room capacity.
     * @return Room capacity
     */
    int getRoomCapacity() const;

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
     * @brief Set the room name.
     * @param room_name Room name
     */
    void setRoomName(const string& room_name);

    /**
     * @brief Set the room capacity.
     * @param capacity Room capacity
     */
    void setRoomCapacity(const int& capacity);
};

/**
 * @brief Print a table of rooms.
 * @param rooms Vector of Room objects
 */
void printRoomsTable(const std::vector<Room>& rooms);

#endif