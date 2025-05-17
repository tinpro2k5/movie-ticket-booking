#ifndef ROOM_H
#define ROOM_H
#include "../../include/models/Movie.h"

class Room {
    private:
    int _id_room;
    int _id_theater;
    string _room_name;
    int _capacity;
    public:
    Room();
    ~Room();
    Room(int id_room, int id_theater, string room_name, int capacity);
    //getter
    int getRoomId() const;
    int getTheaterId() const;
    string getRoomName() const;
    int getRoomCapacity() const;
    //setter
    void setRoomId(int id_room);
    void setTheaterId(int id_theater);
    void setRoomName(string room_name);
    void setRoomCapacity(int capacity);
};
void printRoomsTable(const std::vector<Room>& rooms);
#endif