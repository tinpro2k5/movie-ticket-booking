#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "../../include/repositories/MovieRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
class MovieService{
    std::shared_ptr<MovieRepository> movie_repos;
    public:
    MovieService(RepositoryRegistry& repoRegistry);
    void getListMovie();
    void filterMovies();
    void manageMovies(User user);
    void manageMoviesUI(wxWindow* parent, User user);
};

#endif


