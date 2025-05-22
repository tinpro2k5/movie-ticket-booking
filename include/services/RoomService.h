#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H
#include "../../include/services/ICommand.h"
#include "../../include/repositories/RoomRepository.h"
#include "../../include/app/RepositoryRegistry.h"

#include <wx/wx.h>
#include <wx/listctrl.h>
class RoomService{
    std::shared_ptr<MovieTheaterRepository> movie_theater_repos;
    std::shared_ptr<RoomRepository> room_repos;
    public:
        RoomService(RepositoryRegistry& repoRegistry);
        void manageRoom(User user);
        void manageRoomUI(wxWindow* parent, User user);
};

#endif
