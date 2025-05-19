#ifndef MOVIE_THEATER_H
#define MOVIE_THEATER_H
#include "./Movie.h"

class MovieTheater {
    private:
    int _id_theater;
    string _name;
    string _location;
    public:
    MovieTheater();
    ~MovieTheater();
    MovieTheater(int id_theater, string name, string location);
    //getter
    int getTheaterId() const;
    string getTheaterName() const;
    string getTheaterLocation() const;
    //setter
    void setTheaterId(const int& id_theater);
    void setTheaterName(const string& name);
    void setTheaterLocation(const string& location);
    //

};
void printTheaterTable(const vector<MovieTheater>& theaters);

#endif