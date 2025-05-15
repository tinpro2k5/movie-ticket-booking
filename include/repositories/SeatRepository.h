#ifndef SEATREPOSITORY_H
#define SEATREPOSITORY_H
#include "../../include/models/Seat.h"
#include "../../include/repositories/IRepository.h"
class SeatRepository: public IRepository<Seat> {   
    public:
    Result<vector<Seat>> findByRoomId(int id_room, int id_theater);
    Result<int> create(const Seat& seat) override;
};
#endif
