#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H
#include <string>
#include <iostream>
#include <vector>
#include "../utils/Logger.h"
#include "../utils/PDFGenerator.h"

class EmailService {
public:
    EmailService() = default;
    ~EmailService() = default;
    static bool sendOtp(const std::string& recipient, const std::string& otp);
    static bool sendTicketBookingNotification(const std::string& recipient, const Info & info); 
    static bool sendShowTimeCancelation(const std::string& recipient, const std::string& showTimeDetails);
};



#endif // EMAIL_SERVICE_H
    