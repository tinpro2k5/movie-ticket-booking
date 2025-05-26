/**
 * @file MenuInvoker.h
 * @brief Declares the MenuInvoker class for managing and executing menu commands.
 */

#ifndef MENUINVOKER_H
#define MENUINVOKER_H
#include <map>
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

/**
 * @class MenuInvoker
 * @brief Invoker class for managing and executing user/admin menu commands using the command pattern.
 *
 * Stores a mapping of menu options to ICommand objects and provides methods to display menus and execute commands.
 */
class MenuInvoker{
    std::map<int, ICommand*> commands; /**< Map of menu option to ICommand pointer */
public:
    /**
     * @brief Set a command for a specific menu option.
     * @param option Menu option number
     * @param command Pointer to ICommand object
     */
    void setCommand(int option, ICommand* command) {
        commands[option] = command;
    }

    /**
     * @brief Display the user menu.
     */
    void showMenuUser() {
        std::cout << "===== MENU =====\n";
        std::cout << "1. Xem danh sách phim\n";
        std::cout << "2. Lọc phim\n";
        std::cout << "3. Đặt vé\n";
        std::cout << "4. Xem vé đã đặt\n";
        std::cout << "0. Thoát\n";
        std::cout << "=================\n";
    }

    /**
     * @brief Display the admin menu.
     */
    void showMenuAdmin() {
        std::cout << "===== MENU =====\n";
        std::cout << "1. Quản lí phim\n";
        std::cout << "2. Quản lí suất chiếu\n";
        std::cout << "3. Quản lí rạp\n";
        std::cout << "4. Quản lí phòng vé\n";
        std::cout << "0. Thoát\n";
        std::cout << "=================\n";
    }

    /**
     * @brief Execute a command based on the selected menu option for a user.
     * @param option Menu option number
     * @param user The user performing the action
     */
    void executeCommand(int option, User user) {
        if (commands.count(option)) {
            commands[option]->execute(user);
        } else {
            std::cout << "Lựa chọn không hợp lệ.\n";
        }
    }

    /**
     * @brief Execute a command with UI based on the selected menu option for a user.
     * @param idx Menu option number
     * @param user The user performing the action
     * @param parent The parent wxWindow for the UI
     */
    void executeCommandUI(int idx, User user, wxWindow* parent) {
        if (commands[idx]) commands[idx]->executeUI(user, parent);
    }
};
#endif