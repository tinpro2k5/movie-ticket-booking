/**
 * @file FilterMovieCommand.h
 * @brief Declares the FilterMovieCommand class for filtering movies using the command pattern.
 */

#ifndef FILTERMOVIECOMMAND_H
#define FILTERMOVIECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

/**
 * @class FilterMovieCommand
 * @brief Command class to handle movie filtering actions.
 *
 * Implements the ICommand interface to execute movie filtering logic, both for backend and UI.
 */
class FilterMovieCommand : public ICommand {
    MovieService* service; /**< Pointer to the MovieService used for filtering */
public:

    /**
     * @brief Constructor with MovieService dependency injection.
     * @param service Pointer to MovieService
     */
    FilterMovieCommand(MovieService* service) : service(service) {}

    /**
     * @brief Execute the movie filtering logic.
     * @param user The user requesting the filter
     */
    void execute(User user) override {
        service->filterMovies();
    }

    /**
     * @brief Execute the movie filtering UI logic.
     * @param user The user requesting the filter
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        service->filterMoviesUI(user, parent);
    }
};

#endif