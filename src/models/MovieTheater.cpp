#include "../../include/models/MovieTheater.h"

MovieTheater::MovieTheater(){ //Constructor
    _id_theater = 0;
    _name = "";
    _location = "";
}
MovieTheater::~MovieTheater(){
    // Destructor
}
MovieTheater::MovieTheater(int id_theater, string name, string location){ //Constructor with parameters
    _id_theater = id_theater;
    _name = name;
    _location = location;
}
//getter
int MovieTheater::getTheaterId() const{
    return _id_theater;
}
string MovieTheater::getTheaterName() const{
    return _name;
}
string MovieTheater::getTheaterLocation() const{
    return _location;
}
//setter
void MovieTheater::setTheaterId(int id_theater){
    _id_theater = id_theater;
}
void MovieTheater::setTheaterName(string name){
    _name = name;
}
void MovieTheater::setTheaterLocation(string location){
    _location = location;
}

void printTheaterTable(const std::vector<MovieTheater>& theaters) {
    std::cout << "| " << std::left
              << std::setw(12) << "ID" << " | "
              << std::setw(50) << "Tên rạp" << " | "
              << std::setw(70) << "Địa chỉ" << " |"
              << "\n";

    // In dòng kẻ ngăn cách
    std::cout << "|" << std::string(14, '-') << "|"
              << std::string(52, '-') << "|"
              << std::string(72, '-') << "|" << "\n";

    for (const auto& theater : theaters) {
        std::cout << "| " << std::left
                  << std::setw(12) << theater.getTheaterId() << " | "
                  << std::setw(50) << theater.getTheaterName() << " | "
                  << std::setw(70) << theater.getTheaterLocation() << " |"
                  << "\n";
    }
}