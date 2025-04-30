#include "../../include/utils/OtpGenerator.h"

OtpGenerator* OtpGenerator::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<OtpGenerator>(new OtpGenerator());
    }
    return instance.get();
}
std::string OtpGenerator::generateOtp() {
    std::string otp;
    for (int i = 0; i < OTP_LENGTH; ++i) {
        otp += std::to_string(std::rand() % 10); // Generate a random digit
    }
    return otp;
}