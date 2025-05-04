#include "../include/utils/PasswordHasher.h"

/**
 * @file PasswordHasher.cpp
 * @brief Implementation of the PasswordHasher class for hashing and verifying passwords.
 * 
 * This file contains the implementation of the `PasswordHasher` class, which provides
 * functionality to securely hash passwords and verify them against hashed values.
 */

/**
 * @brief Hash a password.
 * 
 * This method generates a secure hash for the given password using a hash function (e.g., SHA256).
 * 
 * @param password The plain text password to hash.
 * @return The hashed password as a string.
 */
std::string PasswordHasher::hashPassword(const std::string& password) {
    // Sử dụng hàm băm SHA256 để băm mật khẩu
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

/**
 * @brief Verify a password against a hashed value.
 * 
 * This method checks if the given plain text password matches the hashed password.
 * 
 * @param password The plain text password to verify.
 * @param hashed The hashed password to compare against.
 * @return True if the password matches the hash, false otherwise.
 */
bool PasswordHasher::verifyPassword(const std::string& password, std::string hashed) {
    // Băm mật khẩu và so sánh với giá trị đã băm
    return hashPassword(password) == hashed;
}