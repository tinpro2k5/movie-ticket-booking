#include <cassert>
#include <iostream>
#include "../../include/utils/DatabaseManager.h"


void testServerInfoCustomConstructor() {
    ServerInfo server_info("localhost", "root", "password",  3306);
    assert(server_info.getHost() == "localhost");
    assert(server_info.getUser() == "root");
    assert(server_info.getPassword() == "password");
    assert(server_info.getPort() == 3306);
    std::cout << "testServerInfoCustomConstructor passed!\n";
}

void testDatabaseConnectDisconnect() {
    DatabaseManager* db = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "root", "", 3306);

    db->connect(server_info);
    assert(db->getConnection() != nullptr);

    db->disconnect();
    assert(db->getConnection() == nullptr);

    std::cout << "testDatabaseConnectDisconnect passed!\n";
}

void testExecuteSimpleQuery() {
    DatabaseManager* db = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "root", "password",  3306);

    db->connect(server_info);
    QueryResult result = db->executeQuery("SELECT 1;");
    assert(result.success);
    assert(result.result != nullptr); // SELECT 1 trả về kết quả

    db->disconnect();
    std::cout << "testExecuteSimpleQuery passed!\n";
}

void testExecuteScript() {
    DatabaseManager* db = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "root", "password",  3306);

    db->connect(server_info);
    ScriptResult script_result = db->executeScript("../../sql_scripts/init_db.sql");

    assert(script_result.success);

    db->disconnect();
    std::cout << "testExecuteScript passed!\n";
}

void testSetupDatabase() {
    DatabaseManager* db = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "root", "password", 3306);

    db->connect(server_info);
    db->setupDatabase();

    db->disconnect();
    std::cout << "testSetupDatabase passed!\n";
}

int main() {
  
    testServerInfoCustomConstructor();
    testDatabaseConnectDisconnect();
    testExecuteSimpleQuery();
    testExecuteScript();
    testSetupDatabase();

    std::cout << "✅ All tests passed!\n";
    return 0;
}
