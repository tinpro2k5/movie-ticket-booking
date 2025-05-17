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
void Room::setRoomId(int id_room){
    _id_room = id_room;
}
void Room::setTheaterId(int id_theater){
    _id_theater = id_theater;
}
void Room::setRoomName(string room_name){
    _room_name = room_name;
}
void Room::setRoomCapacity(int capacity){ 
    _capacity = capacity;
}

void printRoomsTable(const std::vector<Room>& rooms) {
    std::cout << std::left
              << std::setw(10) << "Room ID"
              << std::setw(12) << "Theater ID"
              << std::setw(25) << "Room Name"
              << std::setw(10) << "Capacity" << "\n";

    std::cout << std::string(10 + 12 + 25 + 10, '-') << "\n";

    for (const auto& room : rooms) {
        std::cout << std::left
                  << std::setw(10) << room.getRoomId()
                  << std::setw(12) << room.getTheaterId()
                  << std::setw(25) << room.getRoomName()
                  << std::setw(10) << room.getRoomCapacity()
                  << "\n";
    }
}