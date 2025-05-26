/**
 * @file RoomRepository.h
 * @brief Declares the RoomRepository class for managing Room data in the database.
 */

#ifndef ROOMREPOSITORY_H
#define ROOMREPOSITORY_H

#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class RoomRepository
 * @brief Provides methods to interact with Room data in the database.
 *
 * Inherits from IRepository<Room> and implements CRUD operations and search functions for rooms.
 */
class RoomRepository: public IRepository<Room> {

    public:
    /**
     * @brief Find all rooms by theater ID.
     * @param id_theater Theater ID
     * @return Result containing a vector of Room objects.
     */
    Result<vector<Room>> findByTheaterId(int id_theater);

    /**
     * @brief Find a room by theater ID and room ID.
     * @param id_theater Theater ID
     * @param id_room Room ID
     * @return Result containing the Room object.
     */
    Result<Room> findById(int id_theater, int id_room);

    /**
     * @brief Retrieve all rooms from the database.
     * @return Result containing a vector of Room objects.
     */
    Result<vector<Room>> findAll();

    /**
     * @brief Add a new room to the database.
     * @param room Room object to add
     * @return Result containing the new room's ID.
     */
    Result<int> create(const Room& room);

    /**
     * @brief Update an existing room in the database.
     * @param room Room object with updated data
     * @return Result indicating success or failure.
     */
    Result<bool> update(const Room& room) override;
};
#endif