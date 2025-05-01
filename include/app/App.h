#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <string>
#include "../app/RepositoryRegistry.h"
#include "../services/UserService.h"
#include "../utils/DatabaseManager.h"
#include "../utils/SessionManager.h"
#include "../utils/Logger.h"


class App {
private:
    RepositoryRegistry repos_res;
    UserService user_service;
public:
    App();
    ~App();
    void startMenu() {
        std::cout << "===== CINEMA BOOKING SYSTEM =====\n";
        std::cout << "1. Đăng ký\n";
        std::cout << "2. Đăng nhập\n";
        std::cout << "0. Thoát\n";
        std::cout << "Nhập lựa chọn của bạn: ";
    }
    int run();
    
};


#endif