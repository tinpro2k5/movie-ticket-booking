#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <string>
#include "../../include/models/User.h"
#include "../services/UserService.h"
class SessionManager {
private:
    inline static User currentUser = User();
    inline static bool loggedIn = false;
    inline static std::string current_otp = "";
    SessionManager(){};  // Không cho khởi tạo đối tượng
    
public:
    static void clear();  // logout
    static User getCurrentUser();
    static bool isLoggedIn();
    static bool isAdminUser();
    static void setCurrentUser(const User& user);
    static void setLoggedIn(bool status);
    static void setCurrentOTP(const std::string& otp);
    static std::string getCurrentOTP();
};  


#endif