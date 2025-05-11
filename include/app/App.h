#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <string>
#include "../app/RepositoryRegistry.h"
#include "../services/UserService.h"
#include "../utils/DatabaseManager.h"
#include "../utils/SessionManager.h"
#include "../utils/Logger.h"
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"
#include "../../include/services/ViewMovieCommand.h"
#include "../../include/services/FilterMovieCommand.h"
#include "../../include/services/MenuInvoker.h"
#include "../../include/services/TicketService.h"
#include "../../include/services/BookTicketCommand.h"
#include "../../include/services/ShowTicketCommand.h"

class App {
private:
    RepositoryRegistry repos_res;
    UserService user_service;
    MovieService movie_service;
    TicketService ticket_service;
    MenuInvoker menu_invoker;
    ViewMovieCommand view_movie_command;
    FilterMovieCommand filter_movie_command;
    BookTicketCommand book_ticket_command;
    ShowTicketCommand show_ticket_command;
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