#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H
#include "../../include/services/ICommand.h"
#include "../../include/repositories/RoomRepository.h"
#include "../../include/app/RepositoryRegistry.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

/**
 * @class RoomService
 * @brief Provides business logic for room-related operations.
 *
 * Handles managing rooms, both in backend logic and with UI integration.
 */
class RoomService{
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos; /**< Shared pointer to the MovieTheaterRepository */
    std::shared_ptr<RoomRepository> room_repos;                  /**< Shared pointer to the RoomRepository */
    public:
        /**
         * @brief Constructor with repository registry dependency injection.
         * @param repoRegistry Reference to the RepositoryRegistry
         */
        RoomService(RepositoryRegistry& repoRegistry);

        /**
         * @brief Manage rooms (add, edit, delete) via console.
         * @param user The user performing the management
         */
        void manageRoom(User user);

        /**
         * @brief Manage rooms (add, edit, delete) via UI.
         * @param parent The parent wxWindow for the UI
         * @param user The user performing the management
         */
        void manageRoomUI(wxWindow* parent, User user);
};

#endif