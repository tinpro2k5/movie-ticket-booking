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
#include "../../include/services/ShowTimeService.h"
#include "../../include/services/MovieManageCommand.h"
#include "../../include/services/ShowTimeManageCommand.h"
#include "../../include/services/RoomService.h"
#include "../../include/services/RoomManageCommand.h"
#include "../../include/services/TheaterService.h"
#include "../../include/services/TheaterManageCommand.h"
class App {
private:
    RepositoryRegistry repos_res;
    UserService user_service;
    MovieService movie_service;
    TicketService ticket_service;
    ShowTimeService show_time_service;
    RoomService room_service;
    TheaterService theater_service;
    MovieManageCommand movie_manage_command;
    ShowTimeManageCommand show_time_manage_command;
    MenuInvoker menu_invoker;
    ViewMovieCommand view_movie_command;
    FilterMovieCommand filter_movie_command;
    BookTicketCommand book_ticket_command;
    ShowTicketCommand show_ticket_command;
    RoomManageCommand room_manage_commnand;
    TheaterManageCommand theater_manage_commnand;
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