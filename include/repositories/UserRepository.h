#ifndef _USER_REPOSITORY_H
#define _USER_REPOSITORY_H

#include <string>
#include <vector>
#include "../../include/models/User.h"
#include "../../include/utils/DatabaseManager.h"
#include "../../include/repositories/Result.h"
#include "../../include/repositories/BaseRepository.h"

class UserRepository: public BaseRepository {
public:
    Result<std::vector<User>> findUserById(int userId);
    Result<std::vector<User>> findUserByUsername(const std::string& username);
    Result<bool> checkExistAccount(const std::string& username, const std::string& email);
    Result<User> save (const User& user);
};


#endif