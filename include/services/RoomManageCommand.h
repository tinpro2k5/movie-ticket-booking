/**
 * @file RoomManageCommand.h
 * @brief Declares the RoomManageCommand class for managing rooms using the command pattern.
 */

#ifndef   ROOMMANAGECOMMAND_H
#define   ROOMMANAGECOMMAND_H

#include "../../include/services/ICommand.h"
#include "../../include/services/RoomService.h"

#include <wx/wx.h>
#include <wx/listctrl.h>

/**
 * @class RoomManageCommand
 * @brief Command class to handle room management actions.
 *
 * Implements the ICommand interface to execute room management logic, both for backend and UI.
 */
class RoomManageCommand : public ICommand {
    RoomService* room_service; /**< Pointer to the RoomService used for management */
public:
    /**
     * @brief Constructor with RoomService dependency injection.
     * @param room_service Pointer to RoomService
     */
    RoomManageCommand(RoomService* room_service) : room_service(room_service) {}

    /**
     * @brief Execute the room management logic for a user.
     * @param user The user performing the action
     */
    void execute(User user) override {
        room_service->manageRoom(user);
    }

    /**
     * @brief Execute the room management UI logic for a user.
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        room_service->manageRoomUI(parent, user);
    }
};

#endif