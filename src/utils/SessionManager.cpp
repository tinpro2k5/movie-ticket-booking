#include "../include/utils/SessionManager.h"

/**
 * @file SessionManager.cpp
 * @brief Implementation of the SessionManager class for managing user sessions.
 * 
 * This file contains the implementation of the `SessionManager` class, which provides
 * functionality to manage user sessions, including login, logout, and OTP handling.
 */

/**
 * @brief Clear the current session.
 * 
 * This method logs out the current user, clears the user details, and resets the OTP.
 */
void SessionManager::clear() {
    currentUser = User();
    loggedIn = false;
    current_otp.clear();
}

/**
 * @brief Get the current logged-in user.
 * 
 * @return The current user as a `User` object.
 */
User SessionManager::getCurrentUser() {
    return currentUser;
}

/**
 * @brief Check if a user is logged in.
 * 
 * @return True if a user is logged in, false otherwise.
 */
bool SessionManager::isLoggedIn() {
    return loggedIn;
}

/**
 * @brief Check if the current user is an admin.
 * 
 * @return True if the current user is an admin, false otherwise.
 */
bool SessionManager::isAdminUser() {
    return currentUser.getIsAdmin();
}

/**
 * @brief Set the current user for the session.
 * 
 * @param user The user to set as the current user.
 */
void SessionManager::setCurrentUser(const User& user) {
    currentUser = user;
}

/**
 * @brief Set the login status for the session.
 * 
 * @param status The login status to set (true for logged in, false for logged out).
 */
void SessionManager::setLoggedIn(bool status) {
    loggedIn = status;
}

/**
 * @brief Set the current OTP for the session.
 * 
 * @param otp The OTP to set.
 */
void SessionManager::setCurrentOTP(const std::string& otp) {
    current_otp = otp;
}

/**
 * @brief Get the current OTP for the session.
 * 
 * @return The current OTP as a string.
 */
std::string SessionManager::getCurrentOTP() {
    return current_otp;
}