#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "../../include/repositories/MovieRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "set"
class MovieService{
    std::shared_ptr<MovieRepository> movie_repos;
    public:
    MovieService(RepositoryRegistry& repoRegistry);
    void getListMovie();
    void getListMovieUI(User user, wxWindow* parent);
    void filterMovies();
    void filterMoviesUI(User user, wxWindow* parent);
    void manageMovies(User user);
    void manageMoviesUI(wxWindow* parent, User user);
};

#endif


