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



/*
g++ src/models/*.cpp src/repositories/*.cpp src/services/*.cpp src/utils/*.cpp src/app/RepositoryRegistry.cpp test/test_manage/trash.cpp -o test/test_manage/trash -lmysqlclient
*/
int main(){
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    User user(3, "jane_doe", "password456", "jane@example.com", "0111222333", false);
    int choice;

    RepositoryRegistry repository_registry;
    MovieService movieService(repository_registry);
    ShowTimeService showTimeService(repository_registry);
    RoomService roomService(repository_registry);
    TheaterService theaterService(repository_registry);
    //
    MovieManageCommand movieManage(&movieService);
    ShowTimeManageCommand showTimeManage(&showTimeService);
    RoomManageCommand roomManage(&roomService);
    TheaterManageCommand theaterManage(&theaterService);
    //
    MenuInvoker menu;
    menu.setCommand(1, &movieManage);
    menu.setCommand(2, &showTimeManage);
    menu.setCommand(3, &theaterManage);
    menu.setCommand(4, &roomManage);

    do {
        menu.showMenuAdmin();
        std::cout << "Chọn chức năng: ";
        std::cin >> choice;
        if (choice != 0)
            menu.executeCommand(choice, user);
    } while (choice != 0);

    return 0;
}