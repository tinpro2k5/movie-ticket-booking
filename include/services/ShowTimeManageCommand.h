/**
 * @file ShowTimeManageCommand.h
 * @brief Declares the ShowTimeManageCommand class for managing showtimes using the command pattern.
 */

#ifndef SHOWTIMEMANAGECOMMAND_H
#define SHOWTIMEMANAGECOMMAND_H

#include "../../include/services/ShowTimeService.h"
#include "../../include/services/ICommand.h"

/**
 * @class ShowTimeManageCommand
 * @brief Command class to handle showtime management actions.
 *
 * Implements the ICommand interface to execute showtime management logic, both for backend and UI.
 */
class ShowTimeManageCommand : public ICommand {
    ShowTimeService* show_time_service; /**< Pointer to the ShowTimeService used for management */
public:
    /**
     * @brief Constructor with ShowTimeService dependency injection.
     * @param show_time_service Pointer to ShowTimeService
     */
    ShowTimeManageCommand(ShowTimeService* show_time_service) : show_time_service(show_time_service) {}

    /**
     * @brief Execute the showtime management logic for a user.
     * @param user The user performing the action
     */
    void execute(User user) override {
        show_time_service->manageShowTime(user);
    }

    /**
     * @brief Execute the showtime management UI logic for a user.
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        show_time_service->manageShowTimeUI(parent, user);
    }
};
#endif