/**
 * @file EmailService.h
 * @brief Declares the EmailService class for sending emails such as OTPs and showtime cancelations.
 */

#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H
#include <string>
#include <iostream>
#include <vector>
#include "../utils/Logger.h"

/**
 * @class EmailService
 * @brief Provides static methods for sending emails (OTP, showtime cancelation, etc.).
 */
class EmailService {
public:
    /**
     * @brief Default constructor.
     */
    EmailService() = default;

    /**
     * @brief Default destructor.
     */
    ~EmailService() = default;

    /**
     * @brief Send an OTP code to the recipient's email.
     * @param recipient Recipient email address
     * @param otp One-time password code
     * @return True if sent successfully, false otherwise
     */
    static bool sendOtp(const std::string& recipient, const std::string& otp);

    /**
     * @brief Send a showtime cancelation email to the recipient.
     * @param recipient Recipient email address
     * @param showTimeDetails Details about the canceled showtime
     * @return True if sent successfully, false otherwise
     */
    static bool sendShowTimeCancelation(const std::string& recipient, const std::string& showTimeDetails);
};

#endif // EMAIL_SERVICE_H