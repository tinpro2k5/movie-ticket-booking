#ifndef MOVIETHEATERREPOSITORIES_H
#define MOVIETHEATERREPOSITORIES_H

#include "include/models/MovieTheater.h"
#include "include/utils/DatabaseManager.h"
#include "include/repositories/Result.h"   
#include "include/repositories/BaseRepository.h"

class MovieTheaterRepository: public BaseRepository {
    public:
    Result<vector<MovieTheater>> findAll();
    Result<MovieTheater> findById(int id_theater);
    Result<bool> insert(const MovieTheater& movie_theater);
    Result<bool> update(const MovieTheater& movie_theater);
};
#endif