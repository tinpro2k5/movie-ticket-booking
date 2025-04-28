#ifndef ROOMREPOSITORIES_H
#define ROOMREPOSITORIES_H

#include "include/models/Room.h"
#include "include/utils/DatabaseManager.h"
#include "include/repositories/Result.h"

class RoomRepositories{
    public:
    Result<vector<Room>>findByTheaterId(int id_theater);
    Result<Room>findById(int id_theater, int id_room);
};
#endif