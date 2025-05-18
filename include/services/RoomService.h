#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H
#include "../../include/services/ICommand.h"
#include "../../include/repositories/RoomRepository.h"
#include "../../include/app/RepositoryRegistry.h"

class RoomService{
    std::shared_ptr<RoomRepository> room_repos;
    public:
        RoomService(RepositoryRegistry& repoRegistry);
        void manageRoom(User user);
};

#endif
