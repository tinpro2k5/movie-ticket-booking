#ifndef _PASSWORD_HASHER_H_
#define _PASSWORD_HASHER_H_

#include <string>
#include <functional>


class PasswordHasher {
public:
    PasswordHasher();
    ~PasswordHasher();

    static std::string hashPassword(const std::string& password);
    static bool verifyPassword(const std::string& password, std::string hashed);
};


#endif