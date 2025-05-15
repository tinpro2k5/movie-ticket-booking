#include <cassert>
#include "../../include/utils/DatabaseManager.h"

void test_connect_and_disconnect() {
    ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
    DatabaseManager* dbManager = DatabaseManager::getInstance();

    dbManager->connect(serverInfo);
    assert(dbManager->getConnection() != nullptr && "Connection failed.");

    dbManager->disconnect();
    assert(dbManager->getConnection() == nullptr && "Disconnection failed.");
}

void test_setup_database() {
    ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
    DatabaseManager* dbManager = DatabaseManager::getInstance();

    dbManager->connect(serverInfo);
    dbManager->setupDatabase();
    dbManager->disconnect();
}

void test_execute_query() {
    ServerInfo serverInfo("127.0.0.1", "root", "rootpassword", 3306);
    DatabaseManager* dbManager = DatabaseManager::getInstance();

    dbManager->connect(serverInfo);
    QueryResult useDbResult = dbManager->executeQuery("USE MOVIE_BOOKING");
    assert(useDbResult.success && "USE MOVIE_BOOKING failed.");

    QueryResult showTablesResult = dbManager->executeQuery("SHOW TABLES");
    assert(showTablesResult.success && "SHOW TABLES query failed.");

    dbManager->disconnect();
}

int main() {
    test_connect_and_disconnect();
    test_setup_database();
    test_execute_query();

    return 0;
}
