#ifndef TICKETREPOSITORY_H
#define TICKETREPOSITORY_H
#include "../../include/models/Ticket.h"
#include "../../include/repositories/BaseRepository.h"

class TicketRepository: public BaseRepository {
    public:
    Result<Ticket> findById(int ticket_id);
    Result<vector<Ticket>> findByUserId(int user_id);
    Result<int> add(const Ticket& ticket);
};
#endif