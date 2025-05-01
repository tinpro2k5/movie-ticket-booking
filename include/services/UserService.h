#ifndef _USER_SERVICE_H_

#define _USER_SERVICE_H_
#include <string>
#include <vector>
#include "../models/User.h"
#include "../repositories/UserRepository.h"
#include "../utils/DatabaseManager.h"
#include "../utils/PasswordHasher.h"
#include "../repositories/UserRepository.h"
#include "../utils/SessionManager.h"
#include "../utils/OtpGenerator.h"
#include "../services/EmailService.h"
#include "../app/RepositoryRegistry.h"
enum class StatusCode {
    SUCCESS = 200,
    FAIL = 500,
    USER_NOT_FOUND = 404,
    USER_ALREADY_EXISTS = 409,
    INVALID_PASSWORD = 401,
    OTP_VERIFICATION_FAILED = 403,
    OTP_VERIFICATION_SUCCESS = 200
};

template<typename T>
struct ServiceResult {
    StatusCode status_code;
    T data;
    std::string message;
};


template<>
struct ServiceResult<void> {
    StatusCode status_code;
    std::string message;
};

class UserService {

private:
    // TODO thêm con trỏ đa hình đến repository
    std::shared_ptr<UserRepository> user_repos;
    ServiceResult<void> setAndSendOTP();
public:
    ~UserService();
    UserService();
    UserService(const RepositoryRegistry& repoRegistry);

    ServiceResult<void> createUser(User user);
    ServiceResult<bool> authenticateUser(const std::string& username, const std::string& password);
    ServiceResult<bool> verifyOTP(const std::string& otp);
    ServiceResult<User> getUserByUsername(const std::string& username); 
    
    //ServiceResult<bool> deleteUser(int userId);
};

#endif
