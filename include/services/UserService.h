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

/**
 * @file UserService.h
 * @brief Header file for the UserService class.
 * 
 * This file contains the declaration of the `UserService` class, which provides
 * methods for user-related operations such as creating users, authenticating users,
 * and verifying OTPs.
 */

/**
 * @enum StatusCode
 * @brief Enumeration for service result status codes.
 * 
 * Defines various status codes for service operations, such as success, failure,
 * user not found, and OTP verification results.
 */
enum class StatusCode {
    SUCCESS = 200, ///< Operation succeeded.
    FAIL = 500, ///< Operation failed.
    USER_NOT_FOUND = 404, ///< User not found.
    USER_ALREADY_EXISTS = 409, ///< User already exists.
    INVALID_PASSWORD = 401, ///< Invalid password.
    OTP_VERIFICATION_FAILED = 403, ///< OTP verification failed.
    OTP_VERIFICATION_SUCCESS = 200 ///< OTP verification succeeded.
};

/**
 * @struct ServiceResult
 * @brief Template structure for service operation results.
 * 
 * Contains the status code, data, and message for a service operation.
 * 
 * @tparam T The type of data returned by the service operation.
 */
template<typename T>
struct ServiceResult {
    StatusCode status_code; ///< Status code of the operation.
    T data; ///< Data returned by the operation.
    std::string message; ///< Message describing the result of the operation.
};

/**
 * @struct ServiceResult<void>
 * @brief Specialization of ServiceResult for void data type.
 * 
 * Contains the status code and message for a service operation that does not return data.
 */
template<>
struct ServiceResult<void> {
    StatusCode status_code; ///< Status code of the operation.
    std::string message; ///< Message describing the result of the operation.
};

/**
 * @class UserService
 * @brief Service class for managing user-related operations.
 * 
 * The `UserService` class provides methods for creating users, authenticating users,
 * verifying OTPs, and retrieving user information. It interacts with the `UserRepository`
 * and other utility classes to perform these operations.
 */
class UserService {
private:
    std::shared_ptr<UserRepository> user_repos; ///< Pointer to the user repository.
    
    /**
     * @brief Generate and send an OTP to the current user.
     * 
     * This method generates a one-time password (OTP), sets it in the session,
     * and sends it to the user's email address.
     * 
     * @return A `ServiceResult<void>` indicating the success or failure of the operation.
     */
    ServiceResult<void> setAndSendOTP();

public:
    /**
     * @brief Destructor for the UserService class.
     */
    ~UserService();

    /**
     * @brief Default constructor for the UserService class.
     */
    UserService();

    /**
     * @brief Constructor for the UserService class with repository registry.
     * 
     * @param repoRegistry The repository registry containing the user repository.
     */
    UserService(const RepositoryRegistry& repoRegistry);

    /**
     * @brief Create a new user.
     * 
     * This method creates a new user by hashing their password and saving their details
     * in the database.
     * 
     * @param user The `User` object containing the user's details.
     * @return A `ServiceResult<void>` indicating the success or failure of the operation.
     */
    ServiceResult<void> createUser(User user);

    /**
     * @brief Authenticate a user.
     * 
     * This method authenticates a user by verifying their username and password.
     * If successful, it sets the user in the session and sends an OTP.
     * 
     * @param username The username of the user.
     * @param password The password of the user.
     * @return A `ServiceResult<bool>` indicating the success or failure of the authentication.
     */
    ServiceResult<bool> authenticateUser(const std::string& username, const std::string& password);

    /**
     * @brief Verify an OTP.
     * 
     * This method verifies the OTP entered by the user against the OTP stored in the session.
     * 
     * @param otp The OTP entered by the user.
     * @return A `ServiceResult<bool>` indicating the success or failure of the OTP verification.
     */
    ServiceResult<bool> verifyOTP(const std::string& otp);

    /**
     * @brief Get a user by their username.
     * 
     * This method retrieves a user's details from the database using their username.
     * 
     * @param username The username of the user.
     * @return A `ServiceResult<User>` containing the user's details if found, or an error message if not.
     */
    ServiceResult<User> getUserByUsername(const std::string& username);


    ServiceResult<void> removeUser(const User& user);
};

#endif
