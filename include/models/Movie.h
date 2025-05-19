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
    int _price;
    public:
    Movie();
    ~Movie();
    Movie(const int& id_movie, const string& title, const string& genre, const string& description, const int& duration, const float& rating, const string& poster_path, const int& price);
    //getter
    int getMovieId() const;
    string getMovieTitle() const;
    string getMovieGenre() const;
    string getMovieDescription() const;
    int getMovieDuration() const;
    float getMovieRating() const;
    string getMoviePosterPath() const;
    int getPrice() const;
    //setter
    void setMovieId(const int& id_movie);
    void setMovieTitle(const string& title);
    void setMovieGenre(const string& genre);
    void setMovieDescription(const string& description);
    void setMovieDuration(const int& duration);
    void setMovieRating(const float& rating);
    void setMoviePosterPath(const string& poster_path);
    void setPrice(const int& price);
    //
};
void printMoviesTable(const std::vector<Movie>& movies);
#endif