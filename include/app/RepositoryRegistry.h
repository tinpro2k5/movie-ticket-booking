#ifndef APP_SERVICEREGISTRY_H
#define APP_SERVICEREGISTRY_H

#include <memory>
#include "../repositories/IRepository.h"
#include "../repositories/MovieRepository.h"
#include "../repositories/MovieTheaterRepository.h"
#include "../repositories/RoomRepository.h"
#include "../repositories/SeatRepository.h"
#include "../repositories/SeatScheduleRepository.h"
#include "../repositories/ShowTimeRepository.h"
#include "../repositories/TicketRepository.h"
#include "../repositories/UserRepository.h"

/**
 * @file RepositoryRegistry.h
 * @brief Header file for the RepositoryRegistry struct.
 * 
 * This file contains the declaration of the `RepositoryRegistry` struct, which provides
 * a centralized registry for accessing various repository instances.
 */

/**
 * @struct RepositoryRegistry
 * @brief Registry for managing repository instances.
 * 
 * The `RepositoryRegistry` struct provides shared pointers to various repository instances,
 * allowing centralized access to repositories for different entities such as users, movies,
 * theaters, rooms, seats, schedules, showtimes, and tickets.
 */
struct RepositoryRegistry {

public:
    /**
     * @brief Shared pointer to the user repository.
     */
    std::shared_ptr<IRepository<User>> user_repos;

    /**
     * @brief Shared pointer to the movie repository.
     */
    std::shared_ptr<IRepository<Movie>> movie_repos;

    /**
     * @brief Shared pointer to the movie theater repository.
     */
    std::shared_ptr<IRepository<MovieTheater>> movie_theater_repos;

    /**
     * @brief Shared pointer to the room repository.
     */
    std::shared_ptr<IRepository<Room>> room_repos;

    /**
     * @brief Shared pointer to the seat repository.
     */
    std::shared_ptr<IRepository<Seat>> seat_repos;

    /**
     * @brief Shared pointer to the seat schedule repository.
     */
    std::shared_ptr<IRepository<SeatSchedule>> seat_schedule_repos;

    /**
     * @brief Shared pointer to the showtime repository.
     */
    std::shared_ptr<IRepository<ShowTime>> show_time_repos;

    /**
     * @brief Shared pointer to the ticket repository.
     */
    std::shared_ptr<IRepository<Ticket>> ticket_repos;


    /**
     * @brief Constructor for the RepositoryRegistry struct.
     * 
     * Initializes shared pointers to repository instances.
     */
    RepositoryRegistry();

    /**
     * @brief Destructor for the RepositoryRegistry struct.
     */
    ~RepositoryRegistry();

    // Other methods if needed
    // For example, to get a specific repository

};

#endif // APP_SERVICEREGISTRY_H