#ifndef OTP_GENERATOR_H
#define OTP_GENERATOR_H

#include <string>
#include <random>
#include <ctime>
#include <memory>

class OtpGenerator {
private:
    inline static std::unique_ptr<OtpGenerator> instance = nullptr;
    static const int OTP_LENGTH = 6;

    OtpGenerator() {
        std::srand((std::time(nullptr))); // Seed the random number generator
    }
public:
    ~OtpGenerator() = default;
    static OtpGenerator* getInstance();
    std::string generateOtp();
};

#endif