#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

//User userId, username, password, email, phone, isAdmin

class User {
    int _user_id;
    std::string _username;
    std::string _password;
    std::string _email;
    std::string _phone;
    bool _is_admin;
public:
    User() : _user_id(0), _username(""), _is_admin(false) {} 
    User (int userId, const std::string& username,
            const std::string& password,
            const std::string& email,
            const std::string& phone,
            bool isAdmin
        ); 

    int getUserId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getEmail() const;
    std::string getPhone() const;
    bool getIsAdmin() const;

    void setUserId(int userId);
    void setUsername(const std::string& username);
    void setPassword(const std::string& password);
    void setEmail(const std::string& email);
    void setPhone(const std::string& phone);
    void setIsAdmin(bool isAdmin);
    void printUserInfo() const;

};



#endif