/**
 * @file BookTicketCommand.h
 * @brief Declares the BookTicketCommand class for booking tickets using the command pattern.
 */

#ifndef BOOKTICKETCOMMAND_H
#define BOOKTICKETCOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/TicketService.h"

/**
 * @class BookTicketCommand
 * @brief Command class to handle ticket booking actions.
 *
 * Implements the ICommand interface to execute ticket booking logic, both for backend and UI.
 */
class BookTicketCommand : public ICommand {
    TicketService* ticket; /**< Pointer to the TicketService used for booking */
public:
    /**
     * @brief Constructor with TicketService dependency injection.
     * @param ticket Pointer to TicketService
     */
    BookTicketCommand(TicketService* ticket) : ticket(ticket) {}

    /**
     * @brief Execute the ticket booking logic for a user.
     * @param user The user booking the ticket
     */
    void execute(User user) override {
        ticket->bookTicket(user);
    }

    /**
     * @brief Execute the ticket booking UI logic for a user.
     * @param user The user booking the ticket
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        ticket->bookTicketUI(user, parent);
    }
};
#endif