#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H
#include <string>
#include <iostream>
#include <vector>
#include "../utils/Logger.h"

class EmailService {
public:
    EmailService() = default;
    ~EmailService() = default;
    static bool sendOtp(const std::string& recipient, const std::string& otp);
    static bool sendShowTimeCancelation(const std::string& recipient, const std::string& showTimeDetails);
};



#endif // EMAIL_SERVICE_H
    