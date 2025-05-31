/**
 * @file App.h
 * @brief Defines the App class - the central coordinator for the movie ticket booking application.
 *
 * The App class is responsible for initializing and managing the core components of the system, including:
 * - Managing repositories via RepositoryRegistry.
 * - Managing business services such as UserService, MovieService, TicketService, ShowTimeService, RoomService, and TheaterService.
 * - Managing commands for user and admin actions (viewing movies, filtering, booking tickets, managing movies, showtimes, rooms, theaters, etc.).
 * - Coordinating user interface flows for both users and administrators.
 * - Integrating utilities such as DatabaseManager, Logger, SessionManager, and CultureFormatter.
 *
 * Architecture overview:
 * - App is the entry point, holding business and UI components.
 * - Services handle business logic and interact with repositories.
 * - Commands encapsulate specific actions, invoked by MenuInvoker.
 * - RepositoryRegistry provides repositories to services.
 * - Utilities support logging, session management, rollback, and data formatting.
 */

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
#include "../utils/CultureFormatter.h"



#include "../utils/RollbackContainer.h"

/**
 * @class App
 * @brief Main application class that coordinates all services, repositories, commands, and UI flows.
 *
 * This class acts as the entry point and central controller for the movie ticket booking system.
 * It initializes and manages all core modules, handles user/admin interactions, and orchestrates
 * the application's business logic and user interface.
 */
class App {
private:
    const std::string INIT_DB_SCRIPT = "init_db.sql";
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
    /**
     * @brief Constructs the App object and initializes all core components.
     */
    App();

    /**
     * @brief Destructor for App, cleans up resources.
     */
    ~App();

    /**
     * @brief Displays the start menu and handles initial user choices.
     */
    void displayStartMenu();

    /**
     * @brief Handles user registration via console interface.
     */
    void handleRegister();

    /**
     * @brief Handles user registration via GUI.
     * @param user The user information to register.
     * @param parent The parent wxWindow for the dialog.
     */
    void handleRegisterUI(const User& user, wxWindow* parent);

    /**
     * @brief Handles user login via console interface.
     */
    void handleLogin();

    /**
     * @brief Handles user login via GUI.
     * @param username The username entered.
     * @param password The password entered.
     * @param parent The parent wxWindow for the dialog.
     */
    void handleLoginUI(const std::string& username, const std::string& password, wxWindow* parent);

    /**
     * @brief Handles application exit and cleanup.
     */
    void handleExit();

    /**
     * @brief Displays and manages the user menu (console).
     */
    void handleUserMenu();

    /**
     * @brief Displays and manages the admin menu (console).
     */
    void handleAdminMenu();

    /**
     * @brief Displays and manages the admin menu (GUI).
     * @param parent The parent wxWindow for the dialog.
     */
    void handleAdminMenuUI(wxWindow* parent);

    /**
     * @brief Displays and manages the user menu (GUI).
     * @param parent The parent wxWindow for the dialog.
     */
    void handleUserMenuUI(wxWindow* parent);

    /**
     * @brief Runs the main application loop.
     * @return Exit code.
     */
    int run();
    
};


#endif