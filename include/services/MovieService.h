#ifndef MOVIESERVICE_H
#define MOVIESERVICE_H

#include "../../include/repositories/MovieRepository.h"
#include "../../include/app/RepositoryRegistry.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "set"

/**
 * @class MovieService
 * @brief Provides business logic for movie-related operations.
 *
 * Handles listing, filtering, and managing movies, both in backend logic and with UI integration.
 */
class MovieService{
    std::shared_ptr<MovieRepository> movie_repos; /**< Shared pointer to the MovieRepository */
    public:
    /**
     * @brief Constructor with repository registry dependency injection.
     * @param repoRegistry Reference to the RepositoryRegistry
     */
    MovieService(RepositoryRegistry& repoRegistry);

    /**
     * @brief Print the list of movies to the console.
     */
    void getListMovie();

    /**
     * @brief Show the list of movies in the UI.
     * @param user The user viewing the list
     * @param parent The parent wxWindow for the UI
     */
    void getListMovieUI(User user, wxWindow* parent);

    /**
     * @brief Filter movies and print the result to the console.
     */
    void filterMovies();

    /**
     * @brief Filter movies and show the result in the UI.
     * @param user The user requesting the filter
     * @param parent The parent wxWindow for the UI
     */
    void filterMoviesUI(User user, wxWindow* parent);

    /**
     * @brief Manage movies (add, edit, delete) via console.
     * @param user The user performing the management
     */
    void manageMovies(User user);

    /**
     * @brief Manage movies (add, edit, delete) via UI.
     * @param parent The parent wxWindow for the UI
     * @param user The user performing the management
     */
    void manageMoviesUI(wxWindow* parent, User user);
};

#endif