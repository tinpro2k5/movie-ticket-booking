#ifndef ROOMREPOSITORY_H
#define ROOMREPOSITORY_H

#include "include/models/Room.h"
#include "include/utils/DatabaseManager.h"
#include "include/repositories/Result.h"

class RoomRepository{
    public:
    Result<vector<Room>>findByTheaterId(int id_theater);
    Result<Room>findById(int id_theater, int id_room);
};
#endif