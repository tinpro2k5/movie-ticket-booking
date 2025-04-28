#include <cassert>
#include <string>
#include "../../include/repositories/UserRepository.h"  // Include header file

// Giả lập đối tượng DatabaseManager
void testFindUserById() {
    // Tạo UserRepository
    UserRepository userRepo;

    // Giả lập tìm người dùng theo userId
    Result<std::vector<User>> result = userRepo.findUserById(1);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 user được trả về
    assert(result.data[0].getUserId() == 1);  // Kiểm tra userId của user trả về
    std::cout << "testFindUserById passed!" << std::endl;
}


void testFindUserByUsername() {
    // Tạo UserRepository
    UserRepository userRepo;

    // Giả lập tìm người dùng theo username
    Result<std::vector<User>> result = userRepo.findUserByUsername("john_doe");
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.size() > 0);  // Có ít nhất 1 user được trả về
    assert(result.data[0].getUsername() == "john_doe");  // Kiểm tra username của user trả về
    std::cout << "testFindUserByUsername passed!" << std::endl;
}


void testSave() {
    // Tạo UserRepository
    UserRepository userRepo;

    // Tạo user mới
    User user(0, "john_doe", "password123", "john@example1.com", "1234567890", false);

    // Giả lập lưu người dùng
    Result<User> result = userRepo.save(user);
    
    // Kiểm tra kết quả trả về
    assert(result.success == true);  // Kết quả thành công
    assert(result.data.getUsername() == "john_doe");  // Kiểm tra username đã lưu đúng
    assert(result.data.getPassword() == "password123");  // Kiểm tra mật khẩu đã lưu đúng
    std::cout << "testSave passed!" << std::endl;
}


int main() {
    // Chạy các unit test
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    testFindUserById();
    testFindUserByUsername();
    testSave();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
