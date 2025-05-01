#ifndef SEATREPOSITORY_H
#define SEATREPOSITORY_H
#include "../../include/models/Seat.h"
#include "../../include/repositories/BaseRepository.h"
class SeatRepository: public BaseRepository {   
    public:
    Result<vector<Seat>> findByRoomId(int id_room, int id_theater);
};
#endif
