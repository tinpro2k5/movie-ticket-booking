#ifndef SHOWTIMEREPOSITORY_H
#define SHOWTIMEREPOSITORY_H

#include "../../include/models/ShowTime.h"
#include "../../include/repositories/BaseRepository.h"

class ShowTimeRepository: public BaseRepository {
    public:
    Result<vector<ShowTime>> findShowTimeByMovieId(int id);
    Result<vector<ShowTime>> findShowTimeByTheaterId(int id);
    Result<bool> add(const ShowTime& showtime);
    Result<bool> update(const ShowTime& showtime);
};
#endif