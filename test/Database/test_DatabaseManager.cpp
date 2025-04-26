#include <cassert>
#include <iostream>
#include "../../include/repositories/DatabaseManager.h"


void testSingleton() {
    DatabaseManager* db1 = DatabaseManager::getInstance();
    DatabaseManager* db2 = DatabaseManager::getInstance();
    
    assert(db1 == db2);
    std::cout << "✅ Singleton test passed.\n";
}

void testDatabaseConnection() {
    DatabaseManager* dbManager = DatabaseManager::getInstance();
    MYSQL* conn = dbManager->getConnection();

    assert(conn != nullptr);
    std::cout << "✅ Database connection test passed.\n";
}

int main() {
    std::cout << "Running DatabaseManager unit tests...\n";

    testSingleton();
    testDatabaseConnection();

    std::cout << "🎉 All tests passed!\n";
    return 0;
}
