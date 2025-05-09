#ifndef MENUINVOKER_H
#define MENUINVOKER_H
#include <map>
#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"

class MenuInvoker{
    std::map<int, ICommand*> commands;
public:
    void setCommand(int option, ICommand* command) {
        commands[option] = command;
    }

    void showMenu() {
        std::cout << "1. Xem danh sách phim\n";
        std::cout << "2. Lọc phim\n";
        std::cout << "3. Đặt vé\n";
        std::cout << "4. Xem vé đã đặt\n";
        std::cout << "0. Thoát\n";
    }

    void executeCommand(int option, User user) {
        if (commands.count(option)) {
            commands[option]->execute(user);
        } else {
            std::cout << "Lựa chọn không hợp lệ.\n";
        }
    }
};
#endif