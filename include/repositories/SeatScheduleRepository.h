#ifndef SEATSCHEDULEREPOSITORY_H
#define SEATSCHEDULEREPOSITORY_H

#include "../../include/models/SeatSchedule.h"
#include "../../include/repositories/IRepository.h"

class SeatScheduleRepository: public IRepository<SeatSchedule> {
    public:
    Result<vector<SeatSchedule>> findAvailableSeats(int id_room, int id_theater, string show_time);
    Result<bool> findSeatById(int id_room, int id_theater, string seat_number, string show_time);
    Result<bool> update(const SeatSchedule& ss) override;
    Result<int> create(const SeatSchedule& ss) override;
};
#endif