#include "../include/services/UserService.h"

ServiceResult<int> UserService::createUser(User user) {
    ServiceResult<int> result;
    auto existingUser = user_repos.findUserByUsername(user.getUsername());
    if (existingUser.success && !existingUser.data.empty()) {
        result.status_code = StatusCode::USER_ALREADY_EXISTS;
        result.message = "User already exists";
        return result;
    }
    
    user.setPassword(PasswordHasher::hashPassword(user.getPassword()));
    auto saveResult = user_repos.save(user);
    if (saveResult.success) {
        result.status_code = StatusCode::SUCCESS;
        result.data = saveResult.data.getUserId();
        result.message = "User created successfully";
    } else {
        result.status_code = StatusCode::FAIL;
        result.message = "Failed to create user";
    }
    return result;
}   
ServiceResult<bool> UserService::authenticateUser(const std::string& username, const std::string& password) {
    ServiceResult<bool> result;
    auto userResult = user_repos.findUserByUsername(username);
    if (userResult.success && !userResult.data.empty()) {
        User user = userResult.data[0];
        if (PasswordHasher::verifyPassword(password, user.getPassword())) {
            result.status_code = StatusCode::SUCCESS;
            result.message = "Authentication successful";
        } else {
            result.status_code = StatusCode::INVALID_PASSWORD;
            result.message = "Invalid password";
        }
        SessionManager::setCurrentUser(user);
        SessionManager::setLoggedIn(false);
        setAndSendOTP();
    } else {
        result.status_code = StatusCode::USER_NOT_FOUND;
        result.message = "User not found";
    }
    return result;
}
ServiceResult<User> UserService::getUserByUsername(const std::string& username) {
    ServiceResult<User> result;
    auto userResult = user_repos.findUserByUsername(username);
    if (userResult.success && !userResult.data.empty()) {
        result.status_code = StatusCode::SUCCESS;
        result.data = userResult.data[0];
        result.message = "User found";
    } else {
        result.status_code = StatusCode::USER_NOT_FOUND;
        result.message = "User not found";
    }
    return result;
}


void UserService::setAndSendOTP() {
    std::string otp = OtpGenerator::getInstance()->generateOtp();
    SessionManager::setCurrentOTP(otp);
    // Send OTP to user's email or phone
    // For demonstration, we will just print it
    std::cout << "OTP sent to user: " << otp << std::endl;
    // In a real application, you would send this OTP to the user's email or phone number
    // For example, using an email service or SMS gateway

}

ServiceResult<bool> UserService::verifyOTP(const std::string& otp) {
    ServiceResult<bool> result;
    if (SessionManager::getCurrentOTP() == otp) {
        result.status_code = StatusCode::OTP_VERIFICATION_SUCCESS;
        result.message = "OTP verification successful";
        SessionManager::setLoggedIn(true);
    } else {
        result.status_code = StatusCode::OTP_VERIFICATION_FAILED;
        result.message = "OTP verification failed";
    }
    return result;
}