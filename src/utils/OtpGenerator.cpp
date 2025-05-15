#include "../../include/utils/OtpGenerator.h"

/**
 * @file OtpGenerator.cpp
 * @brief Implementation of the OtpGenerator class for generating one-time passwords (OTPs).
 * 
 * This file contains the implementation of the `OtpGenerator` class, which provides
 * functionality to generate random numeric OTPs.
 */

/**
 * @brief Get the singleton instance of the OtpGenerator.
 * 
 * This method ensures that only one instance of the OtpGenerator exists in the application.
 * 
 * @return Pointer to the singleton OtpGenerator instance.
 */
OtpGenerator* OtpGenerator::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<OtpGenerator>(new OtpGenerator());
    }
    return instance.get();
}

/**
 * @brief Generate a one-time password (OTP).
 * 
 * This method generates a random numeric OTP of length `OTP_LENGTH`.
 * 
 * @return The generated OTP as a string.
 */
std::string OtpGenerator::generateOtp() {
    std::string otp;
    for (int i = 0; i < OTP_LENGTH; ++i) {
        otp += std::to_string(std::rand() % 10); // Generate a random digit
    }
    return otp;
}