#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <string>
#include <cstdlib>
#include <wx/wx.h>

#include "../app/RepositoryRegistry.h"
#include "../services/UserService.h"
#include "../utils/DatabaseManager.h"
#include "../utils/SessionManager.h"
#include "../utils/Logger.h"
#include "../utils/PDFGenerator.h"

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
#include "../utils/RollbackContainer.h"



class App {
private:
    const std::string INIT_DB_SCRIPT = "init_db.sql";
    const std::string PDF_OUTPUT_DIR = "pdf";
    RepositoryRegistry repository_registry;
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
    void displayStartMenu();
    void handleRegister();
    void handleRegisterUI(const User& user, wxWindow* parent);
    void handleLogin();
    void handleLoginUI(const std::string& username, const std::string& password, wxWindow* parent);
    void handleExit();
    void handleUserMenu();
    void handleAdminMenu();
    

    int run();
    
};


#endif