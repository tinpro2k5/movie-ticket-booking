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

bool EmailService::sendOtp(const std::string& recipient, const std::string& otp) {
    std::string command = "echo \"Subject: Your OTP Code\n\nYour OTP is: " + otp + "\" | msmtp " + recipient;
    bool success = (system(command.c_str()) == 0);
    if (success) {
        std::cout << "OTP sent to " << recipient << std::endl;
    } else {
        std::cerr << "Failed to send OTP to " << recipient << std::endl;
    }
    return success; 
}

#endif // EMAIL_SERVICE_H
    