#ifndef _USER_REPOSITORY_H
#define _USER_REPOSITORY_H

#include "../../include/models/User.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include <string>
#include <vector>


class UserRepository {
public:
    Result<std::vector<User>> findUserById(int userId);
    Result<std::vector<User>> findUserByUsername(const std::string& username);
    Result<bool> checkExistAccount(const std::string& username, const std::string& email);
    Result<User> save (const User& user);
};


#endif