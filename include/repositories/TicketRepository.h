#ifndef TICKETREPOSITORY_H
#define TICKETREPOSITORY_H
#include "../../include/models/Ticket.h"
#include "../../include/repositories/IRepository.h"

class TicketRepository: public IRepository<Ticket> {
    public:
    Result<Ticket> findById(int ticket_id);
    Result<vector<Ticket>> findByUserId(int user_id);
    Result<int> create(const Ticket& ticket);
};
#endif