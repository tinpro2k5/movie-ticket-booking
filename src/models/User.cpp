#include "../../include/models/User.h"
User::User (int userId, const std::string& username,
        const std::string& password,
        const std::string& email,
        const std::string& phone,
        bool isAdmin
    ):
        _user_id(userId),
        _username(username),
        _password(password),
        _email(email),
        _phone(phone),
        _is_admin(isAdmin)
    {}

int User::getUserId() const {
    return _user_id;
}
std::string User::getUsername() const { return _username; }
std::string User::getPassword() const { return _password; }
std::string User::getEmail() const { return _email; }
std::string User::getPhone() const { return _phone; }
bool User::getIsAdmin() const { return _is_admin; }

void User::setUserId(int userId) {  _user_id = userId; } 
void User::setUsername(const std::string& username) { _username = username; }
void User::setPassword(const std::string& password) { _password = password; }
void User::setEmail(const std::string& email) { _email = email; }
void User::setPhone(const std::string& phone) { _phone = phone; }
void User::setIsAdmin(bool isAdmin) { _is_admin = isAdmin; }
void User::printUserInfo() const {
    std::cout << "User ID: " << _user_id << "\n"
              << "Username: " << _username << "\n"
              << "Email: " << _email << "\n"
              << "Phone: " << _phone << "\n"
              << "Is Admin: " << (_is_admin ? "Yes" : "No") << std::endl;
}