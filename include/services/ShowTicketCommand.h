#ifndef SHOWTICKETCOMMAND_H
#define SHOWTICKETCOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/TicketService.h"

class ShowTicketCommand : public ICommand {
    TicketService* ticket;
public:

    ShowTicketCommand(TicketService* ticket) : ticket(ticket) {}

    void execute(User user) override {
        ticket->viewUserTicket(user);
    }
    void executeUI(User user, wxWindow* parent) override {
        ticket->viewUserTicketUI(user, parent);
    }
};
#endif