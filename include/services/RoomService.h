#ifndef ROOMSERVICE_H
#define ROOMSERVICE_H
#include "../../include/services/ICommand.h"
#include "../../include/repositories/RoomRepository.h"
#include "../../include/app/RepositoryRegistry.h"

class RoomService{
    std::shared_ptr<RoomRepository> room_repos;
    public:
        RoomService(RepositoryRegistry& repoRegistry){
            room_repos = std::dynamic_pointer_cast<RoomRepository>(repoRegistry.room_repos);
            if (!room_repos) {
            Logger::getInstance()->log("Failed to cast to RoomRepository", Logger::Level::ERROR);
            std::cerr << "Failed to cast to RoomRepository" << std::endl;
            }
        }
        void manageRoom(User user){
            cout << "===== QUẢN LÝ PHÒNG =====\n";
            cout << "1. Thêm phòng\n";
            cout << "2. Xem danh sách phòng\n";
            cout << "0. Thoát\n";
            cout << "=========================\n";
            int choice;
            cout << "Chọn chức năng: ";
            std::cin >> choice;
            switch (choice) {
                case 1: {
                    Room room;
                    int room_id;
                    cout << "Nhập ID phòng: \n";
                    std::cin >> room_id;
                    while(room_id < 1){
                        cout << "Id không hợp lệ! Nhập lại id > 1\n";
                        std::cin >> room_id;
                    }
                    room.setRoomId(room_id);
                    int theater_id;
                    cout << "Nhập ID rạp: \n";
                    std::cin >> theater_id;
                    while(theater_id < 1){
                        cout << "Id không hợp lệ! Nhập lại id > 1\n";
                        std::cin >> theater_id;
                    }
                    room.setTheaterId(theater_id);
                    int capacity;
                    cout << "Nhập sức chứa phòng: \n";
                    std::cin >> capacity;
                    while(capacity < 1){
                        cout << "Sức chứa không hợp lệ! Nhập lại sức chứa > 1\n";
                        std::cin >> capacity;
                    }
                    room.setRoomCapacity(capacity);
                    string input = "";
                    std::cin.ignore();
                    cout << "Nhập tên phòng: \n";
                    getline(std::cin, input);
                    room.setRoomName(input);
                    Result<int> result = room_repos->create(room);
                    if(!result.success){
                        cout << result.error_message << "\n";
                        return;
                    }else{
                        cout << "Thêm phòng thành công \n";
                    }
                    break;
                }
                case 2: {
                    vector<Room> rooms;
                    Result<vector<Room>> result = room_repos->findAll();
                    if (!result.success) {
                        std::cout << result.error_message << "\n";
                        return;
                    }
                    cout << "=============Danh sách phòng=============\n";
                    for (const auto& room : result.data) {
                        std::cout << "Room ID: " << room.getRoomId() << "\n";
                        std::cout << "Theater ID: " << room.getTheaterId() << "\n";
                        std::cout << "Room Name: " << room.getRoomName() << "\n";
                        std::cout << "Capacity: " << room.getRoomCapacity() << "\n";
                    }
                    cout << "==========================================\n";
                    break;
                }
                default:
                    return;
            }
        }
};

#endif
