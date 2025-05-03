#include "../../include/services/ICommand.h"
#include "../../include/services/MovieService.h"
#include "../../include/services/ViewMovieCommand.h"
#include "../../include/services/FilterMovieCommand.h"
#include "../../include/services/MenuInvoker.h"

/* Compile
g++ src/models/Movie.cpp src/repositories/BaseRepository.cpp src/repositories/MovieRepository.cpp src/utils/Logger.cpp src/utils/DatabaseManager.cpp test/test_service/trash.cpp -o test/test_service/trash -lmysqlclient
 */
int main() {
    DatabaseManager::getInstance()->connect(ServerInfo("127.0.0.1", "root", "rootpassword", 3306));
    DatabaseManager::getInstance()->setupDatabase();
    MovieService movieService;

    ViewMovieCommand viewMovies(&movieService);
    FilterMovieCommand filterMovies(&movieService);

    MenuInvoker menu;
    menu.setCommand(1, &viewMovies);
    menu.setCommand(2, &filterMovies);

    int choice;
    do {
        menu.showMenu();
        std::cout << "Chọn chức năng: ";
        std::cin >> choice;
        if (choice != 0)
            menu.executeCommand(choice);
    } while (choice != 0);

    return 0;
}