#ifndef MovieRepositories_h
#define MovieRepositories_h

#include "include/models/Movie.h"
#include "utils/DatabaseManager.h"

class MovieRepositories {
public:
    static void showMovieList();
    static void editMovie();
    static void deleteMovie();
    static void addNewMovie();
};


#endif