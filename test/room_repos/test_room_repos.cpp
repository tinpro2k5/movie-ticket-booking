#include "../../include/repositories/RoomRepository.h"

#include <cassert>
#include <string>
#include "../../include/repositories/MovieRepository.h"  // Include header file
/*
Cau lenh sau de compile
g++ src/models/Movie.cpp src/models/Room.cpp src/repositories/RoomRepository.cpp src/utils/DatabaseManager.cpp test/room_repos/test_room_repos.cpp -o test/room_repos/test_room_repos -lmysqlclient
*/
// Giả lập đối tượng DatabaseManager
void testFindByTheaterId() {
    // Tạo RoomRepository
    RoomRepository roomRepo;

    // Giả lập tìm phòng theo theaterId
    Result<std::vector<Room>> result = roomRepo.findByTheaterId(1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 room được trả về
    assert(result.data[0].getRoomId() == 1);  // Kiểm tra roomId của room trả về
    std::cout << "testFindRoomByTheaterId passed!" << std::endl;

    for(int i = 0; i < result.data.size(); i++){
        std::cout << "Room ID: " << result.data[i].getRoomId() << std::endl;
        std::cout << "Theater ID: " << result.data[i].getTheaterId() << std::endl;
        std::cout << "Room Name: " << result.data[i].getRoomName() << std::endl;
        std::cout << "Room Capacity: " << result.data[i].getRoomCapacity() << std::endl;
    }
}

void testFindById(){
    // Tạo RoomRepository
    RoomRepository roomRepo;

    // Giả lập tìm phòng theo theaterId và roomId
    Result<Room> result = roomRepo.findById(1, 1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.getRoomId() == 1);  // Kiểm tra roomId của room trả về
    std::cout << "testFindRoomById passed!" << std::endl;

    std::cout << "Room ID: " << result.data.getRoomId() << std::endl;
    std::cout << "Theater ID: " << result.data.getTheaterId() << std::endl;
    std::cout << "Room Name: " << result.data.getRoomName() << std::endl;
    std::cout << "Room Capacity: " << result.data.getRoomCapacity() << std::endl;
}
int main() {
    // Chạy các unit test
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindById();
    cout << "-------------------------" << endl;
    testFindByTheaterId();
    cout << "-------------------------" << endl;
    std::cout << "All tests passed!" << std::endl;

    return 0;
}