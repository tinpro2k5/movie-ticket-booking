#include "../../include/models/Movie.h"

Movie::Movie(){ //Constructor
    _id_movie = 0;
    _title = "";
    _description = "";
    _duration = 0;
    _rating = 0.0;
    _poster_path = "";
}
Movie::~Movie(){
    //Destructor
}
Movie::Movie(const int& id_movie, const string& title, const string& genre, const string& description, const int& duration, const float& rating, const string& poster_path, const int& price){ //Constructor with parameters
    _id_movie = id_movie;
    _title = title;
    _genre = genre;
    _description = description;
    _duration = duration;
    _rating = rating;
    _poster_path = poster_path;
    _price = price;
}
//getter
int Movie::getMovieId() const{
    return _id_movie;
}
string Movie::getMovieTitle() const{
    return _title;
}
string Movie::getMovieGenre() const{
    return _genre;
}
string Movie::getMovieDescription() const{
    return _description;
}
int Movie::getMovieDuration() const{
    return _duration;
}
float Movie::getMovieRating() const{
    return _rating;
}
string Movie::getMoviePosterPath() const{
    return _poster_path;
}
int Movie::getPrice() const{
    return _price;
}
//setter
void Movie::setMovieId(const int& id_movie){
    _id_movie = id_movie;
}
void Movie::setMovieTitle(const string& title){
    _title = title;
}
void Movie::setMovieGenre(const string& genre){
    _genre = genre;
}
void Movie::setMovieDescription(const string& description){
    _description = description;
}
void Movie::setMovieDuration(const int& duration){
    _duration = duration;
}
void Movie::setMovieRating(const float& rating){
    _rating = rating;
}
void Movie::setMoviePosterPath(const string& poster_path){
    _poster_path = poster_path;
}
void Movie::setPrice(const int& price){
    _price = price;
}

void printMoviesTable(const std::vector<Movie>& movies) {
    cout << "| " << left
         << setw(12) << "Movie ID" << " | "
         << setw(30) << "Title" << " | "
         << setw(15) << "Genre" << " | "
         << setw(40) << "Description" << " | "
         << setw(10) << "Duration" << " | "
         << setw(10) << "Rating" << " | "
         << setw(10) << "Price" << " |"
         << endl;

    // In dòng kẻ ngăn cách
    cout << "|" << string(14, '-') << "|"
         << string(32, '-') << "|"
         << string(17, '-') << "|"
         << string(42, '-') << "|"
         << string(12, '-') << "|"
         << string(12, '-') << "|"
         << string(12, '-') << "|" << endl;

    // In từng dòng phim
    for (const Movie& movie : movies) {
        cout << "| " << left
             << setw(12) << movie.getMovieId() << " | "
             << setw(30) << movie.getMovieTitle() << " | "
             << setw(15) << movie.getMovieGenre() << " | "
             << setw(40) << movie.getMovieDescription() << " | "
             << setw(10) << movie.getMovieDuration() << " | "
             << setw(10) << movie.getMovieRating() << " | "
             << std::fixed << std::setprecision(2)
             << setw(10) << NumberFormatter::formatNumber(movie.getPrice(), CultureInfo::get() )<< " |"
             << endl;
    }
}

void printMovieVector(const std::vector<Movie>& movies) {
    cout << "| " << left
         << setw(12) << "Stt" << " | "
         << setw(30) << "Title" << " | "
         << setw(15) << "Genre" << " | "
         << setw(40) << "Description" << " | "
         << setw(10) << "Duration" << " | "
         << setw(10) << "Rating" << " | "
         << setw(10) << "Price" << " |"
         << endl;

    // In dòng kẻ ngăn cách
    cout << "|" << string(14, '-') << "|"
         << string(32, '-') << "|"
         << string(17, '-') << "|"
         << string(42, '-') << "|"
         << string(12, '-') << "|"
         << string(12, '-') << "|"
         << string(12, '-') << "|" << endl;

    // In từng dòng phim
    int stt = 1;
    for (const Movie& movie : movies) {
        cout << "| " << left
             << setw(12) << stt << " | "
             << setw(30) << movie.getMovieTitle() << " | "
             << setw(15) << movie.getMovieGenre() << " | "
             << setw(40) << movie.getMovieDescription() << " | "
             << setw(10) << movie.getMovieDuration() << " | "
             << setw(10) << movie.getMovieRating() << " | "
             << std::fixed << std::setprecision(2)
             << setw(10) << NumberFormatter::formatNumber(movie.getPrice(), CultureInfo::get() )<< " |"
             << endl;
        stt++;
    }
}