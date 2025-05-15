#ifndef _PASSWORD_HASHER_H_
#define _PASSWORD_HASHER_H_

#include <string>
#include <functional>

/**
 * @file PasswordHasher.h
 * @brief Header file for the PasswordHasher class.
 * 
 * This file contains the declaration of the `PasswordHasher` class, which provides
 * functionality to hash passwords and verify hashed passwords.
 */

/**
 * @class PasswordHasher
 * @brief Class for hashing and verifying passwords.
 * 
 * The `PasswordHasher` class provides static methods to securely hash passwords
 * and verify them against hashed values.
 */
class PasswordHasher {
public:
    /**
     * @brief Constructor for the PasswordHasher class.
     */
    PasswordHasher();

    /**
     * @brief Destructor for the PasswordHasher class.
     */
    ~PasswordHasher();

    /**
     * @brief Hash a password.
     * 
     * This method generates a secure hash for the given password using a hash function.
     * 
     * @param password The plain text password to hash.
     * @return The hashed password as a string.
     */
    static std::string hashPassword(const std::string& password);

    /**
     * @brief Verify a password against a hashed value.
     * 
     * This method checks if the given plain text password matches the hashed password.
     * 
     * @param password The plain text password to verify.
     * @param hashed The hashed password to compare against.
     * @return True if the password matches the hash, false otherwise.
     */
    static bool verifyPassword(const std::string& password, std::string hashed);
};

#endif