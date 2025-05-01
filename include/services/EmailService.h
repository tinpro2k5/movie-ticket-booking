#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H
#include <string>
#include <iostream>

class EmailService {
public:
    EmailService() = default;
    ~EmailService() = default;
    static bool sendOtp(const std::string& recipient, const std::string& otp);
};



#endif // EMAIL_SERVICE_H
    