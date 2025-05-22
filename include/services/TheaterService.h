#ifndef THEATERSERVICE_H
#define THEATERSERVICE_H

#include "../../include/repositories/MovieTheaterRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
class TheaterService {
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos;
public:
    TheaterService(RepositoryRegistry& repoRegistry);
    void manageTheater(User user);
    void manageTheaterUI(wxWindow* parent, User user);
};
#endif