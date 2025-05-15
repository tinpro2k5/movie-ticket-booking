#ifndef MOVIEMANAGECOMMAND_H
#define MOVIEMANAGECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

class MovieManageCommand : public ICommand {
    MovieService* movie_service;
public:
    MovieManageCommand(MovieService* movie_service) : movie_service(movie_service) {}

    void execute(User user) override {
        movie_service->manageMovies(user);
    }
};
#endif