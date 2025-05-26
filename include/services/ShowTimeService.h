#ifndef    SHOWTIMESERVICE_H
#define    SHOWTIMESERVICE_H
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/repositories/TicketRepository.h"
#include "../../include/services/EmailService.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

/**
 * @class ShowTimeService
 * @brief Provides business logic for showtime-related operations.
 *
 * Handles managing showtimes, both in backend logic and with UI integration.
 */
class ShowTimeService {
    std::shared_ptr<ShowTimeRepository> show_time_repos;           /**< Shared pointer to the ShowTimeRepository */
    std::shared_ptr<SeatScheduleRepository> seat_schedule_repos;   /**< Shared pointer to the SeatScheduleRepository */
    std::shared_ptr<UserRepository> user_repos;                    /**< Shared pointer to the UserRepository */
    std::shared_ptr<TicketRepository> ticket_repos;                /**< Shared pointer to the TicketRepository */
    std::shared_ptr<RoomRepository> room_repos;                    /**< Shared pointer to the RoomRepository */
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos;   /**< Shared pointer to the MovieTheaterRepository */
    std::shared_ptr<MovieRepository> movie_repos;                  /**< Shared pointer to the MovieRepository */
public:
    /**
     * @brief Constructor with repository registry dependency injection.
     * @param repoRegistry Reference to the RepositoryRegistry
     */
    ShowTimeService(RepositoryRegistry& repoRegistry);

    /**
     * @brief Manage showtimes (add, edit, delete) via console.
     * @param user The user performing the management
     */
    void manageShowTime(User user);

    /**
     * @brief Manage showtimes (add, edit, delete) via UI.
     * @param parent The parent wxWindow for the UI
     * @param user The user performing the management
     */
    void manageShowTimeUI(wxWindow* parent, User user);
};
#endif