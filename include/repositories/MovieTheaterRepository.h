#ifndef MOVIETHEATERREPOSITORIES_H
#define MOVIETHEATERREPOSITORIES_H

#include "../../include/models/MovieTheater.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"   
#include "../../include/repositories/IRepository.h"

class MovieTheaterRepository: public IRepository<MovieTheater> {
    public:
    Result<vector<MovieTheater>> findAll();
    Result<MovieTheater> findById(int id_theater);
    Result<int> create(const MovieTheater& movie_theater);
    Result<bool> update(const MovieTheater& movie_theater);
   // Result<bool> remove(int id_theater);
};
#endif