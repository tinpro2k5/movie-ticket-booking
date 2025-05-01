#ifndef APP_SERVICEREGISTRY_H
#define APP_SERVICEREGISTRY_H

#include <memory>
#include "../repositories/BaseRepository.h"
#include "../repositories/MovieRepository.h"
#include "../repositories/MovieTheaterRepository.h"
#include "../repositories/RoomRepository.h"
#include "../repositories/SeatRepository.h"
#include "../repositories/SeatScheduleRepository.h"
#include "../repositories/ShowTimeRepository.h"
#include "../repositories/TicketRepository.h"
#include "../repositories/UserRepository.h"

struct RepositoryRegistry {

public:
    std::shared_ptr<BaseRepository> user_repos;
    std::shared_ptr<BaseRepository> movie_repos;
    std::shared_ptr<BaseRepository> movie_theater_repos;
    std::shared_ptr<BaseRepository> room_repos;
    std::shared_ptr<BaseRepository> seat_repos;
    std::shared_ptr<BaseRepository> seat_schedule_repos;
    std::shared_ptr<BaseRepository> show_time_repos;
    std::shared_ptr<BaseRepository> ticket_repos;

    RepositoryRegistry();
    ~RepositoryRegistry();
    // Other methods if needed
    // For example, to get a specific repository

};



#endif // APP_SERVICEREGISTRY_H