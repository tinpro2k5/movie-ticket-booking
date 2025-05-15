#include "../../include/services/EmailService.h"

/**
 * @file EmailService.cpp
 * @brief Implementation of the EmailService class for sending OTPs via email.
 * 
 * This file contains the implementation of the `EmailService` class, which provides
 * functionality to send one-time passwords (OTPs) to users via email.
 */

/**
 * @class EmailService
 * @brief Service class for sending emails.
 * 
 * The `EmailService` class provides methods to send emails, such as sending OTPs to users.
 */

/**
 * @brief Send an OTP to a recipient via email.
 * 
 * This method sends an OTP to the specified recipient using the `msmtp` command-line tool.
 * 
 * @param recipient The email address of the recipient.
 * @param otp The OTP to send.
 * @return True if the email was sent successfully, false otherwise.
 */
bool EmailService::sendOtp(const std::string& recipient, const std::string& otp) {
    std::string command = "echo \"Subject: Your OTP Code\n\nYour OTP is: " + otp + "\" | msmtp " + recipient;
    Logger::getInstance()->log("Sending OTP to " + recipient, Logger::Level::INFO);
    bool success = (system(command.c_str()) == 0);
    if (success) {
        std::cout << "OTP sent to " << recipient << std::endl;
    } else {
        std::cerr << "Failed to send OTP to " << recipient << std::endl;
    }
    return success; 
}