#include "../../include/services/EmailService.h"

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