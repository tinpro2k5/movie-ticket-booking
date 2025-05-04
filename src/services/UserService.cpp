#include "../../include/services/UserService.h"

UserService::UserService() {
    // Constructor
}
UserService::~UserService() {
    // Destructor
}

ServiceResult<void> UserService::createUser(User user) {
    ServiceResult<void> result;
    auto existingUser = user_repos->checkExistAccount(user.getUsername(), user.getEmail());
    if (existingUser.success && existingUser.data) {
        result.status_code = StatusCode::USER_ALREADY_EXISTS;
        result.message = "User already exists";
        return result;
    }
    user.setPassword(PasswordHasher::hashPassword(user.getPassword()));
    auto saveResult = user_repos->save(user);
    if (saveResult.success) {
        result.status_code = StatusCode::SUCCESS;
        result.message = "User created successfully";
    } else {
        result.status_code = StatusCode::FAIL;
        result.message = "Failed to create user";
    }
    return result;
}   

ServiceResult<bool> UserService::authenticateUser(const std::string& username, const std::string& password) {
    ServiceResult<bool> result;
    auto userResult = user_repos->findUserByUsername(username);
    if (userResult.success && !userResult.data.empty()) {
        User user = userResult.data[0];
        if (PasswordHasher::verifyPassword(password, user.getPassword())) {
            result.status_code = StatusCode::SUCCESS;
            result.message = "Authentication successful";
            SessionManager::setCurrentUser(user);
            setAndSendOTP();
        } else {
            result.status_code = StatusCode::INVALID_PASSWORD;
            result.message = "Invalid password";
        }
        SessionManager::setLoggedIn(false);
    } else {
        result.status_code = StatusCode::USER_NOT_FOUND;
        result.message = "User not found";
    }
    return result;
}

ServiceResult<User> UserService::getUserByUsername(const std::string& username) {
    ServiceResult<User> result;
    auto userResult = user_repos->findUserByUsername(username);
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


ServiceResult<void> UserService::setAndSendOTP() {
    ServiceResult<void> result;
    std::string otp = OtpGenerator::getInstance()->generateOtp();
    SessionManager::setCurrentOTP(otp);

    std::string userEmail = SessionManager::getCurrentUser().getEmail();
    std::cout << "Sending OTP to: " << userEmail << std::endl;
    bool sendSuccess = EmailService::sendOtp(userEmail, otp);
    
    if (sendSuccess) {
        result.status_code = StatusCode::SUCCESS;
        result.message = "OTP sent successfully";
        std::cout << "OTP has been sent successfully to " << userEmail << std::endl;
    } else {
        result.status_code = StatusCode::FAIL;
        result.message = "Failed to send OTP";
        std::cerr << "Failed to send OTP to " << userEmail << std::endl;
        
    }
    return result;
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

UserService::UserService(const RepositoryRegistry& repoRegistry) {
    user_repos = std::dynamic_pointer_cast<UserRepository>(repoRegistry.user_repos);
    if (!user_repos) {
        std::cerr << "Failed to cast to UserRepository" << std::endl;
    }
}