#ifndef VIEWMOVIECOMMAND_H
#define VIEWMOVIECOMMAND_H
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

class ViewMovieCommand : public ICommand {
    MovieService* service;
public:
    ViewMovieCommand(MovieService* service) : service(service) {}

    void execute(User user) override {
        service->getListMovie();
    }
    void executeUI(User user, wxWindow* parent) override {
        service->getListMovieUI(user, parent);
    }
};

#endif