#ifndef _USER_REPOSITORY_H
#define _USER_REPOSITORY_H

#include <string>
#include <vector>
#include "../../include/models/User.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"

/**
 * @file UserRepository.h
 * @brief Header file for the UserRepository class.
 * 
 * This file contains the declaration of the `UserRepository` class, which provides
 * methods to interact with the database for user-related operations.
 */

/**
 * @class UserRepository
 * @brief Repository class for managing user-related database operations.
 * 
 * The `UserRepository` class provides methods to perform CRUD operations on user data,
 * such as finding users by ID or username, saving new users, and checking account existence.
 */
class UserRepository: public IRepository<User> {
public:
    /**
     * @brief Find a user by their ID.
     * 
     * This method queries the database to find a user with the specified ID.
     * 
     * @param userId The ID of the user to find.
     * @return A `Result` object containing a vector of `User` objects if successful, or an error message if not.
     */
    Result<std::vector<User>> findUserById(int userId);

    /**
     * @brief Find a user by their username.
     * 
     * This method queries the database to find a user with the specified username.
     * 
     * @param username The username of the user to find.
     * @return A `Result` object containing a vector of `User` objects if successful, or an error message if not.
     */
    Result<std::vector<User>> findUserByUsername(const std::string& username);

    /**
     * @brief Check if a user account exists.
     * 
     * This method checks if a user account with the specified username or email already exists in the database.
     * 
     * @param username The username to check.
     * @param email The email to check.
     * @return A `Result` object containing a boolean value (true if the account exists, false otherwise).
     */
    Result<bool> checkExistAccount(const std::string& username, const std::string& email);

    /**
     * @brief Save a new user to the database.
     * 
     * This method inserts a new user record into the database.
     * 
     * @param user The `User` object containing the details of the user to create.
     * @return A `Result` object containing the saved `User` object if successful, or an error message if not.
     */
    Result<int> create (const User& user);

    Result<int> existAdminUser();

    Result<bool> remove(int id) override;
};

#endif