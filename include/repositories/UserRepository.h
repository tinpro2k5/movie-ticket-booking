/**
 * @file UserRepository.h
 * @brief Declares the UserRepository class for user-related database operations in the movie ticket booking system.
 *
 * The UserRepository class provides methods to interact with the database for user management,
 * including finding users, checking account existence, creating users, and more.
 *
 * Architecture overview:
 * - UserRepository implements the IRepository<User> interface, following the repository pattern.
 * - It encapsulates all data access logic related to users, providing a clean API for services.
 * - This separation supports modularity, testability, and maintainability of the application.
 */

#ifndef _USER_REPOSITORY_H
#define _USER_REPOSITORY_H

#include <string>
#include <vector>
#include "../../include/models/User.h"
#include "../../include/models/ShowTime.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/IRepository.h"

/**
 * @class UserRepository
 * @brief Repository class for managing user-related database operations.
 *
 * Provides CRUD and query operations for User entities.
 */
class UserRepository: public IRepository<User> {
public:
    /**
     * @brief Find a user by their ID.
     * @param userId The ID of the user to find.
     * @return Result containing a vector of User objects if successful, or an error message.
     */
    Result<std::vector<User>> findUserById(int userId);

    /**
     * @brief Find a user by their username.
     * @param username The username of the user to find.
     * @return Result containing a vector of User objects if successful, or an error message.
     */
    Result<std::vector<User>> findUserByUsername(const std::string& username);

    /**
     * @brief Check if a user account exists by username or email.
     * @param username The username to check.
     * @param email The email to check.
     * @return Result containing true if the account exists, false otherwise.
     */
    Result<bool> checkExistAccount(const std::string& username, const std::string& email);

    /**
     * @brief Save a new user to the database.
     * @param user The User object to create.
     * @return Result containing the new user's ID if successful, or an error message.
     */
    Result<int> create(const User& user);

    /**
     * @brief Check if an admin user exists in the database.
     * @return Result containing the number of admin users found.
     */
    Result<int> existAdminUser();

    /**
     * @brief Remove a user from the database by username.
     * @param username The username of the user to remove.
     * @return Result indicating success or failure.
     */
    Result<bool> remove(std::string username);

    /**
     * @brief Find users associated with a specific showtime.
     * @param showtime The ShowTime object to search by.
     * @return Result containing a vector of User objects if successful, or an error message.
     */
    Result<std::vector<User>> findUserHavingShowTime(const ShowTime& showtime);
};

#endif