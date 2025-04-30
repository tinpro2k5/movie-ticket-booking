#include <cassert>
#include <iostream>
#include "../../include/services/UserService.h"
#include "../../include/utils/SessionManager.h"

// Reset lại trạng thái giữa các test
void resetSession() {
    SessionManager::setCurrentUser(User());
    SessionManager::setCurrentOTP("");
    SessionManager::setLoggedIn(false);
}

// Test: Tạo user mới thành công
void testCreateUserSuccess() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("alice");
    user.setPassword("pass123");
    user.setEmail("alice@example.com");

    auto result = service.createUser(user);
    assert(result.status_code == StatusCode::SUCCESS);
    std::cout << "[PASSED] testCreateUserSuccess\n";
}

// Test: Tạo user trùng tên
void testCreateUserDuplicate() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("bob");
    user.setPassword("pass123");
    user.setEmail("bob@example.com");

    service.createUser(user); // Lần đầu
    auto result2 = service.createUser(user); // Lần 2 - trùng
    assert(result2.status_code == StatusCode::USER_ALREADY_EXISTS);
    std::cout << "[PASSED] testCreateUserDuplicate\n";
}

// Test: Đăng nhập thành công
void testAuthenticateUserSuccess() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("charlie");
    user.setPassword("secret");
    user.setEmail("letrungtin12052005@gmail.com");

    service.createUser(user);
    std::cout << "DEBUG: " << user.getEmail() << std::endl;
    auto result = service.authenticateUser("charlie", "secret");
    assert(result.status_code == StatusCode::SUCCESS);
    std::cout << "[PASSED] testAuthenticateUserSuccess\n";
}

// Test: Đăng nhập sai mật khẩu
void testAuthenticateWrongPassword() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("dave");
    user.setPassword("mypassword");
    user.setEmail("dave@example.com");

    service.createUser(user);
    auto result = service.authenticateUser("dave", "wrongpass");
    assert(result.status_code == StatusCode::INVALID_PASSWORD);
    std::cout << "[PASSED] testAuthenticateWrongPassword\n";
}

// Test: Đăng nhập user không tồn tại
void testAuthenticateNonExistentUser() {
    resetSession();
    UserService service;
    auto result = service.authenticateUser("ghost", "nopass");
    assert(result.status_code == StatusCode::USER_NOT_FOUND);
    std::cout << "[PASSED] testAuthenticateNonExistentUser\n";
}

// Test: Xác thực OTP đúng
void testVerifyOTPSuccess() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("eve");
    user.setPassword("123456");
    user.setEmail("zzh60193@toaik.com");

    service.createUser(user);
    service.authenticateUser("eve", "123456");

    std::string correctOtp = SessionManager::getCurrentOTP();
    auto result = service.verifyOTP(correctOtp);
    assert(result.status_code == StatusCode::OTP_VERIFICATION_SUCCESS);
    assert(SessionManager::isLoggedIn());
    std::cout << "[PASSED] testVerifyOTPSuccess\n";
}

// Test: Xác thực OTP sai
void testVerifyOTPFailure() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("frank");
    user.setPassword("abcdef");
    user.setEmail("zzh60193@toaik.com");

    service.createUser(user);
    service.authenticateUser("frank", "abcdef");

    auto result = service.verifyOTP("wrongotp");
    assert(result.status_code == StatusCode::OTP_VERIFICATION_FAILED);
    assert(!SessionManager::isLoggedIn());
    std::cout << "[PASSED] testVerifyOTPFailure\n";
}

// Test: Lấy user theo username thành công
void testGetUserByUsernameSuccess() {
    resetSession();
    UserService service;
    User user;
    user.setUsername("grace");
    user.setPassword("aaa");
    user.setEmail("grace@example.com");

    service.createUser(user);
    auto result = service.getUserByUsername("grace");
    assert(result.status_code == StatusCode::SUCCESS);
    assert(result.data.getEmail() == "grace@example.com");
    std::cout << "[PASSED] testGetUserByUsernameSuccess\n";
}

// Test: Lấy user không tồn tại
void testGetUserByUsernameNotFound() {
    resetSession();
    UserService service;
    auto result = service.getUserByUsername("nonexistent");
    assert(result.status_code == StatusCode::USER_NOT_FOUND);
    std::cout << "[PASSED] testGetUserByUsernameNotFound\n";
}

// Main test runner
int main() {
    ServerInfo serverInfo;
    serverInfo.setHost("127.0.0.1");
    serverInfo.setPort(3306);
    serverInfo.setUser("root");
    serverInfo.setPassword("rootpassword");
  
    
    DatabaseManager::getInstance()->connect(serverInfo);
    DatabaseManager::getInstance()->setupDatabase();
    testCreateUserSuccess();
    testCreateUserDuplicate();
    testAuthenticateUserSuccess();
    testAuthenticateWrongPassword();
    testAuthenticateNonExistentUser();
    testVerifyOTPSuccess();
    testVerifyOTPFailure();
    testGetUserByUsernameSuccess();
    testGetUserByUsernameNotFound();
    std::cout << "\n✅ All unit tests passed!\n";
    return 0;
}
