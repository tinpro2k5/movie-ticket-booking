#ifndef SHOWTIMEREPOSITORY_H
#define SHOWTIMEREPOSITORY_H

#include "../../include/models/ShowTime.h"
#include "../../include/repositories/IRepository.h"

class ShowTimeRepository: public IRepository<ShowTime> {
    public:
    Result<vector<ShowTime>> findShowTimeByMovieId(int id);
    Result<vector<ShowTime>> findShowTimeByTheaterId(int id);
    Result<ShowTime> findExactlyShowTime(int id, string showtime);
    Result<int> create(const ShowTime& showtime) override;
    Result<bool> update(const ShowTime& showtime) override;
    Result<bool> remove(const ShowTime& showtime) ;
};
#endif