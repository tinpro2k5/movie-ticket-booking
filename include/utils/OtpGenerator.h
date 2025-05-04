#ifndef OTP_GENERATOR_H
#define OTP_GENERATOR_H

#include <string>
#include <random>
#include <ctime>
#include <memory>

/**
 * @file OtpGenerator.h
 * @brief Header file for the OtpGenerator class.
 * 
 * This file contains the declaration of the `OtpGenerator` class, which provides
 * functionality to generate one-time passwords (OTPs).
 */

/**
 * @class OtpGenerator
 * @brief Singleton class for generating one-time passwords (OTPs).
 * 
 * The `OtpGenerator` class provides methods to generate random numeric OTPs of a fixed length.
 * It ensures that only one instance of the generator exists in the application.
 */
class OtpGenerator {
private:
    inline static std::unique_ptr<OtpGenerator> instance = nullptr; ///< Singleton instance.
    static const int OTP_LENGTH = 6; ///< Length of the generated OTP.

    /**
     * @brief Private constructor to enforce singleton pattern.
     * 
     * Seeds the random number generator with the current time.
     */
    OtpGenerator() {
        std::srand((std::time(nullptr))); // Seed the random number generator
    }

public:
    /**
     * @brief Destructor for the OtpGenerator class.
     */
    ~OtpGenerator() = default;

    /**
     * @brief Get the singleton instance of the OtpGenerator.
     * 
     * This method ensures that only one instance of the OtpGenerator exists in the application.
     * 
     * @return Pointer to the singleton OtpGenerator instance.
     */
    static OtpGenerator* getInstance();

    /**
     * @brief Generate a one-time password (OTP).
     * 
     * This method generates a random numeric OTP of length `OTP_LENGTH`.
     * 
     * @return The generated OTP as a string.
     */
    std::string generateOtp();
};

#endif