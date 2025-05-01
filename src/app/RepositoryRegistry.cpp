#include "../../include/app/RepositoryRegistry.h"

RepositoryRegistry::RepositoryRegistry() {
    user_repos = std::make_shared<UserRepository>();
    movie_repos = std::make_shared<MovieRepository>();
    movie_theater_repos = std::make_shared<MovieTheaterRepository>();
    room_repos = std::make_shared<RoomRepository>();
    seat_repos = std::make_shared<SeatRepository>();
    seat_schedule_repos = std::make_shared<SeatScheduleRepository>();
    show_time_repos = std::make_shared<ShowTimeRepository>();
    ticket_repos = std::make_shared<TicketRepository>();
}

RepositoryRegistry::~RepositoryRegistry() {}