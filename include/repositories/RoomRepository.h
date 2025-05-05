#ifndef ROOMREPOSITORY_H
#define ROOMREPOSITORY_H

#include "../../include/models/Room.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"

class RoomRepository: public IRepository<Room> {

    public:
    Result<vector<Room>>findByTheaterId(int id_theater);
    Result<Room>findById(int id_theater, int id_room);
    Result<int> create(const Room& room);
};
#endif