#include <cassert>
#include "../../include/repositories/TicketRepository.h"

void testFindById() {
    TicketRepository ticketRepo;
    Result<Ticket> result = ticketRepo.findById(1);
    assert(result.success == true);
    assert(result.data.getTicketId() == 1);

    cout << "Ticket ID: " << result.data.getTicketId() << endl;
    cout << "User ID: " << result.data.getUserId() << endl;
    cout << "Room ID: " << result.data.getRoomId() << endl;
    cout << "Theater ID: " << result.data.getTheaterId() << endl;
    cout << "Seat Number: " << result.data.getSeatNumber() << endl;
    cout << "Show Time: " << result.data.getShowTime() << endl;
    cout << "Price: " << result.data.getPrice() << endl;
    cout << "Booking Time: " << result.data.getBookingTime() << endl;
    cout << "Is Paid: " << (result.data.isPaid() ? "Yes" : "No") << endl;
    cout << "testFindById passed!" << endl;

}
void testFindByUserId() {
    TicketRepository ticketRepo;
    Result<vector<Ticket>> result = ticketRepo.findByUserId(1);
    assert(result.success == true);
    assert(result.data.size() > 0);
    assert(result.data[0].getUserId() == 1);
    for (int i = 0; i < result.data.size(); i++) {
        cout << "Ticket ID: " << result.data[i].getTicketId() << endl;
        cout << "User ID: " << result.data[i].getUserId() << endl;
        cout << "Room ID: " << result.data[i].getRoomId() << endl;
        cout << "Theater ID: " << result.data[i].getTheaterId() << endl;
        cout << "Seat Number: " << result.data[i].getSeatNumber() << endl;
        cout << "Show Time: " << result.data[i].getShowTime() << endl;
        cout << "Price: " << result.data[i].getPrice() << endl;
        cout << "Booking Time: " << result.data[i].getBookingTime() << endl;
        cout << "Is Paid: " << (result.data[i].isPaid() ? "Yes" : "No") << endl;
    }
    cout << "testFindByUserId passed!" << endl;
}
int main(){
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindById();
    cout << "----------------------------------------" << endl;
    testFindByUserId();
    cout << "----------------------------------------" << endl;
    return 0;
}