/**
 * @file TicketRepository.h
 * @brief Declares the TicketRepository class for managing Ticket data in the database.
 */

#ifndef TICKETREPOSITORY_H
#define TICKETREPOSITORY_H
#include "../../include/models/Ticket.h"
#include "../../include/models/ShowTime.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class TicketRepository
 * @brief Provides methods to interact with Ticket data in the database.
 *
 * Inherits from IRepository<Ticket> and implements CRUD operations and search functions for tickets.
 */
class TicketRepository: public IRepository<Ticket> {
    public:
    /**
     * @brief Find a ticket by its ID.
     * @param ticket_id Ticket ID
     * @return Result containing the Ticket object.
     */
    Result<Ticket> findById(int ticket_id);

    /**
     * @brief Find all tickets by user ID.
     * @param user_id User ID
     * @return Result containing a vector of Ticket objects.
     */
    Result<vector<Ticket>> findByUserId(int user_id);

    /**
     * @brief Add a new ticket to the database.
     * @param ticket Ticket object to add
     * @return Result containing the new ticket's ID.
     */
    Result<int> create(const Ticket& ticket);

    /**
     * @brief Find all tickets for a specific showtime.
     * @param showtime ShowTime object
     * @return Result containing a vector of Ticket objects.
     */
    Result<vector<Ticket>> findHavingShowTime(const ShowTime& showtime); 
};
#endif