/**
 * @file TheaterManageCommand.h
 * @brief Declares the TheaterManageCommand class for managing theaters using the command pattern.
 */

#ifndef THEATERMANAGECOMMAND_H
#define THEATERMANAGECOMMAND_H

#include "../../include/services/ICommand.h"
#include "../../include/services/TheaterService.h"

/**
 * @class TheaterManageCommand
 * @brief Command class to handle theater management actions.
 *
 * Implements the ICommand interface to execute theater management logic, both for backend and UI.
 */
class TheaterManageCommand : public ICommand {
    TheaterService* theater_service; /**< Pointer to the TheaterService used for management */
public:
    /**
     * @brief Constructor with TheaterService dependency injection.
     * @param theater_service Pointer to TheaterService
     */
    TheaterManageCommand(TheaterService* theater_service) : theater_service(theater_service) {}

    /**
     * @brief Execute the theater management logic for a user.
     * @param user The user performing the action
     */
    void execute(User user) override {
        theater_service->manageTheater(user);
    }

    /**
     * @brief Execute the theater management UI logic for a user.
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        theater_service->manageTheaterUI(parent,user);
    }
};
#endif