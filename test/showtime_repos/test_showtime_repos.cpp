#include <cassert>
#include <string>
#include "../../include/repositories/ShowTimeRepository.h"  // Include header file
/*
Cau lenh sau de compile
g++ src/models/Movie.cpp src/models/ShowTime.cpp src/models/Room.cpp src/repositories/ShowTimeRepository.cpp src/utils/DatabaseManager.cpp test/showtime_repos/test_showtime_repos.cpp -o test/showtime_repos/test_showtime_repos -lmysqlclient
*/
// Giả lập đối tượng DatabaseManager
void testFindShowTimeByMovieId() {
    // Tạo ShowTimeRepository
    ShowTimeRepository showtimeRepo;

    // Giả lập tìm phòng theo theaterId
    Result<std::vector<ShowTime>> result = showtimeRepo.findShowTimeByMovieId(1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 room được trả về
    assert(result.data[0].getMovieId() == 1);  // Kiểm tra roomId của room trả về
    std::cout << "testFindShowTimeByMovieId passed!" << std::endl;

    for(int i = 0; i < result.data.size(); i++){
        std::cout << "Room ID: " << result.data[i].getRoomId() << std::endl;
        std::cout << "Theater ID: " << result.data[i].getTheaterId() << std::endl;
        std::cout << "Show Time: " << result.data[i].getShowTime() << std::endl;
        std::cout << "Movie ID: " << result.data[i].getMovieId() << std::endl;
    }
}
void testFindShowTimeByTheaterId(){
    // Tạo ShowTimeRepository
    ShowTimeRepository showtimeRepo;

    // Giả lập tìm phòng theo theaterId và roomId
    Result<std::vector<ShowTime>> result = showtimeRepo.findShowTimeByTheaterId(1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 room được trả về
    assert(result.data[0].getTheaterId() == 1);  // Kiểm tra roomId của room trả về
    std::cout << "testFindShowTimeByTheaterId passed!" << std::endl;

    for(int i = 0; i < result.data.size(); i++){
        std::cout << "Room ID: " << result.data[i].getRoomId() << std::endl;
        std::cout << "Theater ID: " << result.data[i].getTheaterId() << std::endl;
        std::cout << "Show Time: " << result.data[i].getShowTime() << std::endl;
        std::cout << "Movie ID: " << result.data[i].getMovieId() << std::endl;
    }
}
void testAdd() {
    // Tạo ShowTimeRepository
    ShowTimeRepository showtimeRepo;

    // Tạo một đối tượng ShowTime mới
    ShowTime newShowTime(1, 1, "2023-10-01 10:00:00", 1);

    // Giả lập thêm một showtime mới
    Result<bool> result = showtimeRepo.add(newShowTime);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    std::cout << "testAddShowTime passed!" << std::endl;
}
void testUpdate() {
    // Tạo ShowTimeRepository
    ShowTimeRepository showtimeRepo;

    // Tạo một đối tượng ShowTime mới
    ShowTime updatedShowTime(1, 1, "2023-10-01 12:00:00", 1);

    // Giả lập cập nhật một showtime mới
    Result<bool> result = showtimeRepo.update(updatedShowTime);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    std::cout << "testUpdateShowTime passed!" << std::endl;
}
int main() {
    // Chạy các unit test
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindShowTimeByMovieId();
    cout << "-------------------------" << endl;
    testAdd();
    cout << "-------------------------" << endl;
    //testUpdate();
    cout << "-------------------------" << endl;
    testFindShowTimeByTheaterId();
    cout << "-------------------------" << endl;
    std::cout << "All tests passed!" << std::endl;

    return 0;
}