#ifndef TICKETSERVICE_H
#define TICKETSERVICE_H

#include "../../include/repositories/TicketRepository.h"
#include "../../include/repositories/SeatRepository.h"
#include "../../include/repositories/MovieRepository.h"

#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/models/User.h"
#include "../../include/repositories/SeatScheduleRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include "../utils/PricingRule.h"
#include "../utils/PDFGenerator.h"

class TicketService{
    std::shared_ptr<TicketRepository> ticket_repos;
    std::shared_ptr<ShowTimeRepository> showtime_repos;
    std::shared_ptr<MovieRepository> movie_repos;
    std::shared_ptr<SeatScheduleRepository> ss_repos;
    std::shared_ptr<SeatRepository> seat_repos;
public:
    TicketService(RepositoryRegistry& repoRegistry);
    void bookTicket(User user);
    void viewUserTicket(User user);
};



#endif