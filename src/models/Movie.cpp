#include "include/models/Movie.h"

Movie::Movie(string id_movie, string name, string genre, string format, string show_date, string show_time, string ticket_price, string seat)
{
    _id_movie = id_movie;
    _name = name;
    _genre = genre;
    _format = format;
    _show_date = show_date;
    _show_time = show_time;
    _ticket_price = ticket_price;
    _seat = seat;
}

Movie::~Movie(){
}
string Movie::getIdMovie() const{
    return _id_movie;
}
string Movie::getName() const{
    return _name;
}
string Movie::getGenre() const{
    return _genre;
}
string Movie::getFormat() const{
    return _format;
}
string Movie::getShowDate() const{
    return _show_date;
}
string Movie::getShowTime() const{
    return _show_time;
}
string Movie::getTicketPrice() const{
    return _ticket_price;
}
string Movie::getSeat() const{
    return _seat;
}
void Movie::setIdMovie(const string& id_movie) {
    _id_movie = id_movie;
}
void Movie::setName(const string& name) {
    _name = name;
}

void Movie::setGenre(const string& genre) {
    _genre = genre;
}

void Movie::setFormat(const string& format) {
    _format = format;
}

void Movie::setShowDate(const string& show_date) {
    _show_date = show_date;
}

void Movie::setShowTime(const string& show_time) {
    _show_time = show_time;
}

void Movie::setTicketPrice(const string& ticket_price) {
    _ticket_price = ticket_price;
}

void Movie::setSeat(const string& seat) {
    _seat = seat;
}
ostream& operator<<(ostream& os, const Movie& movie){
    cout << "| " << setw(15) << left << movie._id_movie
         << "| " << setw(15) << left << movie._name
         << "| " << setw(15) << left << movie._genre
         << "| " << setw(15) << left << movie._format
         << "| " << setw(15) << left << movie._show_date
         << "| " << setw(15) << left << movie._show_time
         << "| " << setw(15) << left << movie._ticket_price
         << "| " << setw(15) << left << movie._seat
         << "|" << endl;
}