#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <memory.h>
#include <exception>
#include <string>
#include <cstdlib>
#include <mysql/mysql.h>
#include <vector>
#include <algorithm>
#include <iomanip>
using std::string, std::ostream,std::cout, std::endl, std::setw, std::left, std::vector;
class Movie{
    private:
    int _id_movie;
    string _title;
    string _genre;
    string _description;
    int _duration;
    float _rating;
    string _poster_path;
    public:
    Movie();
    ~Movie();
    Movie(int id_movie, string title, string genre, string description, int duration, float rating, string poster_path);
    //getter
    int getMovieId() const;
    string getMovieTitle() const;
    string getMovieGenre() const;
    string getMovieDescription() const;
    int getMovieDuration() const;
    float getMovieRating() const;
    string getMoviePosterPath() const;
    //setter
    void setMovieId(int id_movie);
    void setMovieTitle(string title);
    void setMovieGenre(string genre);
    void setMovieDescription(string description);
    void setMovieDuration(int duration);
    void setMovieRating(float rating);
    void setMoviePosterPath(string poster_path);
};
#endif