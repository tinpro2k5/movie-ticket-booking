#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include "../../include/repositories/TicketRepository.h"
#include "../../include/repositories/SeatRepository.h"
#include "../../include/repositories/MovieRepository.h"
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/models/User.h"
#include "../../include/repositories/SeatScheduleRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include "../utils/PricingRule.h"
#include "../utils/CultureFormatter.h"

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <set>

/**
 * @class TicketService
 * @brief Provides business logic for ticket-related operations.
 *
 * Handles booking and viewing tickets, both in backend logic and with UI integration.
 */
class TicketService{
    std::shared_ptr<TicketRepository> ticket_repos;              /**< Shared pointer to the TicketRepository */
    std::shared_ptr<ShowTimeRepository> showtime_repos;          /**< Shared pointer to the ShowTimeRepository */
    std::shared_ptr<MovieRepository> movie_repos;                /**< Shared pointer to the MovieRepository */
    std::shared_ptr<SeatScheduleRepository> ss_repos;            /**< Shared pointer to the SeatScheduleRepository */
    std::shared_ptr<SeatRepository> seat_repos;                  /**< Shared pointer to the SeatRepository */
    std::shared_ptr<MovieTheaterRepository> theater_repos;       /**< Shared pointer to the MovieTheaterRepository */
public:
    /**
     * @brief Constructor with repository registry dependency injection.
     * @param repoRegistry Reference to the RepositoryRegistry
     */
    TicketService(RepositoryRegistry& repoRegistry);

    /**
     * @brief Book a ticket for a user (console).
     * @param user The user booking the ticket
     */
    void bookTicket(User user);

    /**
     * @brief Book a ticket for a user (UI).
     * @param user The user booking the ticket
     * @param parent The parent wxWindow for the UI
     */
    void bookTicketUI(User user, wxWindow* parent);

    /**
     * @brief View tickets booked by a user (console).
     * @param user The user viewing their tickets
     */
    void viewUserTicket(User user);

    /**
     * @brief View tickets booked by a user (UI).
     * @param user The user viewing their tickets
     * @param parent The parent wxWindow for the UI
     */
    void viewUserTicketUI(User user, wxWindow* parent);
};

#endif