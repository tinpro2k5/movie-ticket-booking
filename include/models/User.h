#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

/**
 * @file User.h
 * @brief Header file for the User class.
 * 
 * This file contains the declaration of the `User` class, which represents a user in the system.
 * It includes user details such as ID, username, password, email, phone, and admin status.
 */

/**
 * @class User
 * @brief Class representing a user in the system.
 * 
 * The `User` class provides methods to manage user details, including getters and setters
 * for user attributes and a method to print user information.
 */
class User {
    int _user_id; ///< Unique identifier for the user.
    std::string _username; ///< Username of the user.
    std::string _password; ///< Password of the user.
    std::string _email; ///< Email address of the user.
    std::string _phone; ///< Phone number of the user.
    bool _is_admin; ///< Admin status of the user (true if admin, false otherwise).

public:
    /**
     * @brief Default constructor for the User class.
     * 
     * Initializes the user with default values.
     */
    User() : _user_id(0), _username(""), _is_admin(false) {}

    /**
     * @brief Parameterized constructor for the User class.
     * 
     * @param userId The unique identifier for the user.
     * @param username The username of the user.
     * @param password The password of the user.
     * @param email The email address of the user.
     * @param phone The phone number of the user.
     * @param isAdmin The admin status of the user.
     */
    User(int userId, const std::string& username,
         const std::string& password,
         const std::string& email,
         const std::string& phone,
         bool isAdmin);

    /**
     * @brief Get the user ID.
     * @return The unique identifier for the user.
     */
    int getUserId() const;

    /**
     * @brief Get the username.
     * @return The username of the user.
     */
    std::string getUsername() const;

    /**
     * @brief Get the password.
     * @return The password of the user.
     */
    std::string getPassword() const;

    /**
     * @brief Get the email address.
     * @return The email address of the user.
     */
    std::string getEmail() const;

    /**
     * @brief Get the phone number.
     * @return The phone number of the user.
     */
    std::string getPhone() const;

    /**
     * @brief Get the admin status.
     * @return True if the user is an admin, false otherwise.
     */
    bool getIsAdmin() const;

    /**
     * @brief Set the user ID.
     * @param userId The unique identifier for the user.
     */
    void setUserId(int userId);

    /**
     * @brief Set the username.
     * @param username The username of the user.
     */
    void setUsername(const std::string& username);

    /**
     * @brief Set the password.
     * @param password The password of the user.
     */
    void setPassword(const std::string& password);

    /**
     * @brief Set the email address.
     * @param email The email address of the user.
     */
    void setEmail(const std::string& email);

    /**
     * @brief Set the phone number.
     * @param phone The phone number of the user.
     */
    void setPhone(const std::string& phone);

    /**
     * @brief Set the admin status.
     * @param isAdmin The admin status of the user.
     */
    void setIsAdmin(bool isAdmin);

    /**
     * @brief Print user information.
     * 
     * This method prints the details of the user to the console.
     */
    void printUserInfo() const;
};

#endif