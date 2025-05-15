#ifndef SHOWTIMEMANAGECOMMAND_H
#define SHOWTIMEMANAGECOMMAND_H

#include "../../include/services/ShowTimeService.h"
#include "../../include/services/ICommand.h"

class ShowTimeManageCommand : public ICommand {
    ShowTimeService* show_time_service;
public:
    ShowTimeManageCommand(ShowTimeService* show_time_service) : show_time_service(show_time_service) {}

    void execute(User user) override {
        show_time_service->manageShowTime(user);
    }
};
#endif