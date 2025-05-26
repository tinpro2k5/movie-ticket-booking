#ifndef THEATERSERVICE_H
#define THEATERSERVICE_H

#include "../../include/repositories/MovieTheaterRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

/**
 * @class TheaterService
 * @brief Provides business logic for theater-related operations.
 *
 * Handles managing theaters, both in backend logic and with UI integration.
 */
class TheaterService {
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos; /**< Shared pointer to the MovieTheaterRepository */
public:
    /**
     * @brief Constructor with repository registry dependency injection.
     * @param repoRegistry Reference to the RepositoryRegistry
     */
    TheaterService(RepositoryRegistry& repoRegistry);

    /**
     * @brief Manage theaters (add, edit, delete) via console.
     * @param user The user performing the management
     */
    void manageTheater(User user);

    /**
     * @brief Manage theaters (add, edit, delete) via UI.
     * @param parent The parent wxWindow for the UI
     * @param user The user performing the management
     */
    void manageTheaterUI(wxWindow* parent, User user);
};
#endif