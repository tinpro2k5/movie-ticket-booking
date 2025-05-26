/**
 * @file ICommand.h
 * @brief Declares the ICommand interface for command pattern actions.
 */

#ifndef ICOMMAND_H
#define ICOMMAND_H
#include "../../include/models/User.h"

class wxWindow; // Forward declaration

/**
 * @class ICommand
 * @brief Interface for command pattern actions.
 *
 * Provides an interface for executing commands, both in backend logic and with UI integration.
 */
class ICommand{
    public:
    /**
     * @brief Execute the command logic for a user.
     * @param user The user performing the action
     */
    virtual void execute(User user) = 0;

    /**
     * @brief Execute the command logic with UI for a user.
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    virtual void executeUI(User user, wxWindow* parent) { }

    /**
     * @brief Virtual destructor.
     */
    virtual ~ICommand() {}
};
#endif