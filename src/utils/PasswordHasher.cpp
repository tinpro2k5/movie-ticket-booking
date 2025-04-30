#include "../include/utils/PasswordHasher.h"

std::string PasswordHasher::hashPassword(const std::string& password) {
    // Sử dụng hàm băm SHA256 để băm mật khẩu
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

bool PasswordHasher::verifyPassword(const std::string& password, std::string hashed) {
    // Băm mật khẩu và so sánh với giá trị đã băm
    return hashPassword(password) == hashed;
}