#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include "include/models/User.h"

class SessionManager {
    private:
        static User currentUser;
        static bool loggedIn;
        SessionManager() {}  // Không cho khởi tạo đối tượng
    
    public:
        static void login(const std::string& username, const std::string& password);
        static void logout();
        static const User& getCurrentUser();
        static bool isLoggedIn();
        static bool isAdminUser();
};  


#endif