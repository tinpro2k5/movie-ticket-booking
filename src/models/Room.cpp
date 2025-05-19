#include "../../include/models/Room.h"

Room::Room(){ //Constructor
    _id_room = 0;
    _id_theater = 0;
    _room_name = "";
    _capacity = 0;
}
Room::~Room(){
    // Destructor
}
Room::Room(int id_room, int id_theater, string room_name, int capacity){ // Constructor wwith parameters
    _id_room = id_room;
    _id_theater = id_theater;
    _room_name = room_name;
    _capacity = capacity;
}
//getter
int Room::getRoomId() const{
    return _id_room;
}
int Room::getTheaterId() const{
    return _id_theater;
}
string Room::getRoomName() const{
    return _room_name;
}
int Room::getRoomCapacity() const{
    return _capacity;
}
//setter
void Room::setRoomId(const int& id_room){
    _id_room = id_room;
}
void Room::setTheaterId(const int& id_theater){
    _id_theater = id_theater;
}
void Room::setRoomName(const string& room_name){
    _room_name = room_name;
}
void Room::setRoomCapacity(const int& capacity){ 
    _capacity = capacity;
}

void printRoomsTable(const std::vector<Room>& rooms) {
    std::cout << "| " << std::left
              << std::setw(12) << "Room ID" << " | "
              << std::setw(15) << "Theater ID" << " | "
              << std::setw(30) << "Room Name" << " | "
              << std::setw(10) << "Capacity" << " |"
              << "\n";

    // In dòng kẻ ngăn cách
    std::cout << "|" << std::string(14, '-') << "|"
              << std::string(17, '-') << "|"
              << std::string(32, '-') << "|"
              << std::string(12, '-') << "|" << "\n";

    for (const auto& room : rooms) {
        std::cout << "| " << std::left
                  << std::setw(12) << room.getRoomId() << " | "
                  << std::setw(15) << room.getTheaterId() << " | "
                  << std::setw(30) << room.getRoomName() << " | "
                  << std::setw(10) << room.getRoomCapacity() << " |"
                  << "\n";
    }
}