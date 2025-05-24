#ifndef BOOKTICKETCOMMAND_H
#define BOOKTICKETCOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/TicketService.h"

class BookTicketCommand : public ICommand {
    TicketService* ticket;
public:

    BookTicketCommand(TicketService* ticket) : ticket(ticket) {}

    void execute(User user) override {
        ticket->bookTicket(user);
    }
    void executeUI(User user, wxWindow* parent) override {
        ticket->bookTicketUI(user, parent);
    }
};
#endif