#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>

//User userId, username, password, email, phone, isAdmin

class User {
    int userId;
    std::string username;
    std::string password;
    std::string email;
    std::string phone;
    bool isAdmin;
public:
    User() : userId(0), username(""), isAdmin(false) {} 
    User(int userId, const std::string& username, const std::string& password, const std::string& email, const std::string& phone, bool isAdmin);
    ~User();

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