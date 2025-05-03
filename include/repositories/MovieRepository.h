#ifndef MOVIEREPOSITORY_H
#define MOVIEREPOSITORY_H

#include "../../include/models/Movie.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/BaseRepository.h"
class MovieRepository: public BaseRepository {
    public:
        //Get movie lists
        Result<vector<Movie>> findAll();
        //Get movie by id
        Result<Movie> findById(int id_movie);
        //Get movie by genre
        Result<vector<Movie>> findByGenre(string genre);
        //Get movie by name
        Result<vector<Movie>> findByName(string name);
        //Add movie
        Result<bool> add(const Movie& movie);
        //Update movie
        Result<bool> update(const Movie& movie);
        //Delete movie
        Result<bool> remove(int id_movie);
};
#endif