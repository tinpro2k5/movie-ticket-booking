#ifndef TICKETREPOSITORY_H
#define TICKETREPOSITORY_H
#include "../../include/models/Ticket.h"

class TicketRepository {
    public:
    Result<Ticket> findById(int ticket_id);
    Result<vector<Ticket>> findByUserId(int user_id);
};
#endif