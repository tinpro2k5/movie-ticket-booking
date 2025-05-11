#ifndef   ROOMMANAGECOMMAND_H
#define   ROOMMANAGECOMMAND_H

#include "../../include/services/ICommand.h"
#include "../../include/services/RoomService.h"
class RoomManageCommand : public ICommand {
    RoomService* room_service;
public:
    RoomManageCommand(RoomService* room_service) : room_service(room_service) {}
    void execute(User user) {
        room_service->manageRoom(user);
    }
};

#endif