#ifndef FILTERMOVIECOMMAND_H
#define FILTERMOVIECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

class FilterMovieCommand : public ICommand {
    MovieService* service;
public:

    FilterMovieCommand(MovieService* service) : service(service) {}

    void execute(User user) override {
        service->filterMovies();
    }
    void executeUI(User user, wxWindow* parent) override {
        service->filterMoviesUI(user, parent);
    }
};

#endif