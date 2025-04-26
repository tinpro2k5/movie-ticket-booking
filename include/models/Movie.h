#ifndef Movie_h
#define Movie_h


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
using std::string, std::ostream,std::cout, std::endl, std::setw, std::left;
class Movie{
    private:
    string _id_movie;
    string _name;
    string _genre;
    string _format;
    string _show_date;
    string _show_time;
    string _ticket_price;
    string _seat;
    public:
    Movie(string id_movie, string name, string genre, string format, string show_date, string show_time, string ticket_price, string seat);
    ~Movie();
    //getters
    string getIdMovie() const;
    string getName() const;
    string getGenre() const;
    string getFormat() const;
    string getShowDate() const;
    string getShowTime() const;
    string getTicketPrice() const;
    string getSeat() const;
    //setters
    void setIdMovie(const string& id_movie);
    void setName(const string& name);
    void setGenre(const string& genre);
    void setFormat(const string& format);
    void setShowDate(const string& show_date);
    void setShowTime(const string& show_time);
    void setTicketPrice(const string& ticket_price);
    void setSeat(const string& seat);
    //print method
    friend ostream& operator<<(ostream& os, const Movie& movie);
};
#endif