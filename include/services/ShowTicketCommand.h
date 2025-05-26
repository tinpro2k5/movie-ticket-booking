/**
 * @file ShowTicketCommand.h
 * @brief Declares the ShowTicketCommand class for viewing tickets using the command pattern.
 */

#ifndef SHOWTICKETCOMMAND_H
#define SHOWTICKETCOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/TicketService.h"

/**
 * @class ShowTicketCommand
 * @brief Command class to handle viewing user tickets.
 *
 * Implements the ICommand interface to execute ticket viewing logic, both for backend and UI.
 */
class ShowTicketCommand : public ICommand {
    TicketService* ticket; /**< Pointer to the TicketService used for viewing tickets */
public:

    /**
     * @brief Constructor with TicketService dependency injection.
     * @param ticket Pointer to TicketService
     */
    ShowTicketCommand(TicketService* ticket) : ticket(ticket) {}

    /**
     * @brief Execute the ticket viewing logic for a user.
     * @param user The user viewing their tickets
     */
    void execute(User user) override {
        ticket->viewUserTicket(user);
    }

    /**
     * @brief Execute the ticket viewing UI logic for a user.
     * @param user The user viewing their tickets
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        ticket->viewUserTicketUI(user, parent);
    }
};
#endif