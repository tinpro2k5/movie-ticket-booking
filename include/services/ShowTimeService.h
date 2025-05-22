#ifndef    SHOWTIMESERVICE_H
#define    SHOWTIMESERVICE_H
#include "../../include/repositories/ShowTimeRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include "../../include/repositories/UserRepository.h"
#include "../../include/repositories/TicketRepository.h"
#include "../../include/services/EmailService.h"

#include <wx/wx.h>
#include <wx/listctrl.h>
class ShowTimeService {
    std::shared_ptr<ShowTimeRepository> show_time_repos;
    std::shared_ptr<SeatScheduleRepository> seat_schedule_repos;
    std::shared_ptr<UserRepository> user_repos;
    std::shared_ptr<TicketRepository> ticket_repos;
    std::shared_ptr<RoomRepository> room_repos;
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos;
    std::shared_ptr<MovieRepository> movie_repos;
public:
    ShowTimeService(RepositoryRegistry& repoRegistry);
    void manageShowTime(User user);
    void manageShowTimeUI(wxWindow* parent, User user);
};
#endif