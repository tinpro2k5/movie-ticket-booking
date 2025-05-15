#include "../../include/repositories/SeatRepository.h"
#include <cassert>
#include <string>
void testFindByRoomId() {
    SeatRepository seatRepo;
    Result<vector<Seat>> result = seatRepo.findByRoomId(1, 1); 

    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 seat được trả về
    assert(result.data[0].getRoomId() == 1);  // Kiểm tra id_room của seat trả về

    for(int i = 0; i < result.data.size(); i++) {
        std::cout << "Room ID: " << result.data[i].getRoomId() << std::endl;
        std::cout << "Theater ID: " << result.data[i].getTheaterId() << std::endl;
        std::cout << "Seat Number: " << result.data[i].getSeatNumber() << std::endl;
        std::cout << "Is VIP: " << (result.data[i].isVip() ? "Yes" : "No") << std::endl;
    }
    std::cout << "testFindByRoomId passed!" << std::endl;
}

int main(){
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindByRoomId();
    cout << "All tests passed!" << std::endl;
    return 0;
}