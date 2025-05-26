/**
 * @file MovieManageCommand.h
 * @brief Declares the MovieManageCommand class for managing movies using the command pattern.
 */

#ifndef MOVIEMANAGECOMMAND_H
#define MOVIEMANAGECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

/**
 * @class MovieManageCommand
 * @brief Command class to handle movie management actions.
 *
 * Implements the ICommand interface to execute movie management logic, both for backend and UI.
 */
class MovieManageCommand : public ICommand {
    MovieService* movie_service; /**< Pointer to the MovieService used for management */
public:
    /**
     * @brief Constructor with MovieService dependency injection.
     * @param movie_service Pointer to MovieService
     */
    MovieManageCommand(MovieService* movie_service) : movie_service(movie_service) {}

    /**
     * @brief Execute the movie management logic for a user.
     * @param user The user performing the action
     */
    void execute(User user) override {     
        movie_service->manageMovies(user);
    }

    /**
     * @brief Execute the movie management UI logic for a user.
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    void executeUI(User user, wxWindow* parent) override {
        movie_service->manageMoviesUI(parent, user);
    }
};
#endif