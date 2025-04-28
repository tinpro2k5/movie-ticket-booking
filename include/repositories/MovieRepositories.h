#ifndef MovieRepositories_h
#define MovieRepositories_h

#include "include/models/Movie.h"
#include "include/utils/DatabaseManager.h"
#include "include/repositories/Result.h"
class MovieRepositories {
    public:
        //Get movie lists
        Result<vector<Movie>> getAllMovies();
        //Get movie by id
        Result<Movie> getMovieById(int id_movie);
        //Add movie
        Result<bool>addMovie(const Movie& movie);
        //Update movie
        Result<bool> updateMovie(const Movie& movie);
        //Delete movie
        Result<bool> deleteMovie(int id_movie);
};
#endif