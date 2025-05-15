#include "../../include/repositories/SeatScheduleRepository.h"
#include <cassert>
void testFindAvailableSeats() {
    SeatScheduleRepository seatScheduleRepo;
    Result<vector<SeatSchedule>> result = seatScheduleRepo.findAvailableSeats(1, 1, "2025-05-01 18:00:00");
    assert(result.success == true);
    assert(result.data.size() > 0);
    for (int i = 0; i < result.data.size(); i++) {
        cout << "Room ID: " << result.data[i].getRoomId() << endl;
        cout << "Theater ID: " << result.data[i].getTheaterId() << endl;
        cout << "Seat Number: " << result.data[i].getSeatNumber() << endl;
        cout << "Show Time: " << result.data[i].getShowTime() << endl;
        cout << "Ticket ID: " << result.data[i].getTicketId() << endl;
    }
    cout << "testFindAvailableSeats passed!" << endl;
}
void testFindSeatById() {
    SeatScheduleRepository seatScheduleRepo;
    Result<bool> result = seatScheduleRepo.findSeatById(1, 1, "A2", "2025-05-01 18:00:00");
    assert(result.success == true);
    assert(result.data == true);
    if(result.data){
        cout << "Seat is available!" << endl;
    }else{
        cout << "Seat is not available!" << endl;
    }
    cout << "testFindSeatById passed!" << endl;
}
int main(){
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindAvailableSeats();
    cout << "----------------------------------------" << endl;
    testFindSeatById();
    cout << "----------------------------------------" << endl;
    return 0;
}