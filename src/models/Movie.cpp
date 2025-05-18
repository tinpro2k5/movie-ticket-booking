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
Movie::Movie(int id_movie, string title, string genre, string description, int duration, float rating, string poster_path, int price){ //Constructor with parameters
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
void Movie::setMovieId(int id_movie){
    _id_movie = id_movie;
}
void Movie::setMovieTitle(string title){
    _title = title;
}
void Movie::setMovieGenre(string genre){
    _genre = genre;
}
void Movie::setMovieDescription(string description){
    _description = description;
}
void Movie::setMovieDuration(int duration){
    _duration = duration;
}
void Movie::setMovieRating(float rating){
    _rating = rating;
}
void Movie::setMoviePosterPath(string poster_path){
    _poster_path = poster_path;
}
void Movie::setPrice(int price){
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
             << setw(10) << movie.getPrice() << " |"
             << endl;
    }
}