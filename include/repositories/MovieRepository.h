#ifndef MOVIEREPOSITORY_H
#define MOVIEREPOSITORY_H

#include "../../include/models/Movie.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"
class MovieRepository: public IRepository<Movie> {
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
        Result<int> create(const Movie& movie);
        //Update movie
        Result<bool> update(const Movie& movie);
        //Delete movie
        Result<bool> remove(int id_movie);
};
#endif