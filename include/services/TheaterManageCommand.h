#ifndef THEATERMANAGECOMMAND_H
#define THEATERMANAGECOMMAND_H

#include "../../include/services/ICommand.h"
#include "../../include/services/TheaterService.h"

class TheaterManageCommand : public ICommand {
    TheaterService* theater_service;
public:
    TheaterManageCommand(TheaterService* theater_service) : theater_service(theater_service) {}

    void execute(User user) override {
        theater_service->manageTheater(user);
    }
};
#endif