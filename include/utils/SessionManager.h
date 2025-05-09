#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>
#include "../../include/models/User.h"
#include "../../include/utils/Logger.h"

/**
 * @file SessionManager.h
 * @brief Header file for the SessionManager class.
 * 
 * This file contains the declaration of the `SessionManager` class, which provides
 * functionality to manage user sessions, including login, logout, and OTP handling.
 */

/**
 * @class SessionManager
 * @brief Singleton-like class for managing user sessions.
 * 
 * The `SessionManager` class provides static methods to manage the current user session,
 * including login status, user details, and OTP handling. It ensures that only one session
 * is active at a time.
 */
class SessionManager {
private:
    inline static User currentUser = User(); ///< The currently logged-in user.
    inline static bool loggedIn = false; ///< Login status of the current session.
    inline static std::string current_otp = ""; ///< The current OTP for the session.

    /**
     * @brief Private constructor to prevent instantiation.
     */
    SessionManager(){};  

public:
    /**
     * @brief Clear the current session.
     * 
     * This method logs out the current user, clears the user details, and resets the OTP.
     */
    static void clear();

    /**
     * @brief Get the current logged-in user.
     * 
     * @return The current user as a `User` object.
     */
    static User getCurrentUser();

    /**
     * @brief Check if a user is logged in.
     * 
     * @return True if a user is logged in, false otherwise.
     */
    static bool isLoggedIn();

    /**
     * @brief Check if the current user is an admin.
     * 
     * @return True if the current user is an admin, false otherwise.
     */
    static bool isAdminUser();

    /**
     * @brief Set the current user for the session.
     * 
     * @param user The user to set as the current user.
     */
    static void setCurrentUser(const User& user);

    /**
     * @brief Set the login status for the session.
     * 
     * @param status The login status to set (true for logged in, false for logged out).
     */
    static void setLoggedIn(bool status);

    /**
     * @brief Set the current OTP for the session.
     * 
     * @param otp The OTP to set.
     */
    static void setCurrentOTP(const std::string& otp);

    /**
     * @brief Get the current OTP for the session.
     * 
     * @return The current OTP as a string.
     */
    static std::string getCurrentOTP();
};  

#endif