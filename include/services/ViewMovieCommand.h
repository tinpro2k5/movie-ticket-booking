/**
 * @file ViewMovieCommand.h
 * @brief Declares the ViewMovieCommand class for viewing movies using the command pattern.
 */

#ifndef VIEWMOVIECOMMAND_H
#define VIEWMOVIECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

/**
 * @class ViewMovieCommand
 * @brief Command class to handle viewing the list of movies.
 *
 * Implements the ICommand interface to execute movie viewing logic, both for backend and UI.
 */
class ViewMovieCommand : public ICommand {
    MovieService* service; /**< Pointer to the MovieService used for viewing movies */
public:
    /**
     * @brief Constructor with MovieService dependency injection.
     * @param service Pointer to MovieService
     */
    ViewMovieCommand(MovieService* service) : service(service) {}

    /**
     * @brief Execute the movie viewing logic for a user.
     * @param user The user viewing the movies
     */
    void execute(User user) override {
        service->getListMovie();
    }

    /**
     * @brief Execute the movie viewing UI logic for a user.
     * @param user The user viewing the movies
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        service->getListMovieUI(user, parent);
    }
};

#endif