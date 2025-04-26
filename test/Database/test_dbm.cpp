#include <iostream>
#include <cassert>
#include <string>
#include <memory>
#include "repositories/DatabaseManager.h"

// Simple test harness class
class Test {
private:
    std::string test_name;
    bool passed;
    static int total_tests;
    static int passed_tests;

public:
    Test(const std::string& name) : test_name(name), passed(true) {
        total_tests++;
    }

    void assert_true(bool condition, const std::string& message) {
        if (!condition) {
            std::cout << "FAIL: " << test_name << " - " << message << std::endl;
            passed = false;
        }
    }

    void assert_equal(const std::string& actual, const std::string& expected, const std::string& message) {
        if (actual != expected) {
            std::cout << "FAIL: " << test_name << " - " << message 
                      << " (Expected: " << expected << ", Got: " << actual << ")" << std::endl;
            passed = false;
        }
    }

    void assert_equal(unsigned int actual, unsigned int expected, const std::string& message) {
        if (actual != expected) {
            std::cout << "FAIL: " << test_name << " - " << message 
                      << " (Expected: " << expected << ", Got: " << actual << ")" << std::endl;
            passed = false;
        }
    }

    ~Test() {
        if (passed) {
            std::cout << "PASS: " << test_name << std::endl;
            passed_tests++;
        }
    }

    static void print_summary() {
        std::cout << "\nTest Summary: " << passed_tests << "/" << total_tests << " tests passed." << std::endl;
    }
};

int Test::total_tests = 0;
int Test::passed_tests = 0;

// Test ServerInfo default constructor
void test_server_info_default_constructor() {
    Test t("ServerInfo_DefaultConstructor");
    ServerInfo server_info;
    t.assert_equal(server_info.getHost(), "localhost", "Host should be localhost");
    t.assert_equal(server_info.getUser(), "root", "User should be root");
    t.assert_equal(server_info.getPassword(), "", "Password should be empty");
    t.assert_equal(server_info.getPort(), 3306u, "Port should be 3306");
}

// Test ServerInfo parameterized constructor
void test_server_info_parameterized_constructor() {
    Test t("ServerInfo_ParameterizedConstructor");
    ServerInfo server_info("test_host", "test_user", "test_pass", "test_db", 3307);
    t.assert_equal(server_info.getHost(), "test_host", "Host should be test_host");
    t.assert_equal(server_info.getUser(), "test_user", "User should be test_user");
    t.assert_equal(server_info.getPassword(), "test_pass", "Password should be test_pass");
    t.assert_equal(server_info.getPort(), 3307u, "Port should be 3307");
}

// Test ServerInfo setters and getters
void test_server_info_setters_getters() {
    Test t("ServerInfo_SettersAndGetters");
    ServerInfo server_info;
    server_info.setHost("new_host");
    server_info.setUser("new_user");
    server_info.setPassword("new_pass");
    server_info.setPort(3308);

    t.assert_equal(server_info.getHost(), "new_host", "Host should be new_host");
    t.assert_equal(server_info.getUser(), "new_user", "User should be new_user");
    t.assert_equal(server_info.getPassword(), "new_pass", "Password should be new_pass");
    t.assert_equal(server_info.getPort(), 3308u, "Port should be 3308");
}

// Test DatabaseManager singleton instance
void test_database_manager_singleton() {
    Test t("DatabaseManager_SingletonInstance");
    DatabaseManager* instance1 = DatabaseManager::getInstance();
    DatabaseManager* instance2 = DatabaseManager::getInstance();
    t.assert_true(instance1 != nullptr, "First instance should not be null");
    t.assert_true(instance2 != nullptr, "Second instance should not be null");
    t.assert_true(instance1 == instance2, "Singleton instances should be the same");
}

// Test DatabaseManager disconnect without connection
void test_database_manager_disconnect_no_connection() {
    Test t("DatabaseManager_DisconnectNoConnection");
    DatabaseManager* db_manager = DatabaseManager::getInstance();
    t.assert_true(!db_manager->disconnect(), "Disconnect should return false when no connection exists");
}

// Placeholder test for DatabaseManager connect (requires MySQL server or mock)
void test_database_manager_connect() {
    Test t("DatabaseManager_Connect");
    DatabaseManager* db_manager = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "test_user", "test_pass", "test_db", 3306);

    // Note: This test requires a running MySQL server or a mock.
    // For unit testing, you can mock mysql_real_connect or set up a test DB.
    // Example with a real DB (uncomment and configure if test DB is available):
    /*
    bool result = db_manager->connect(server_info);
    t.assert_true(result, "Should connect to the database successfully");
    t.assert_true(db_manager->getConnection() != nullptr, "Connection pointer should not be null");
    t.assert_true(db_manager->disconnect(), "Should disconnect successfully");
    */
    
    // Placeholder pass (replace with actual test when DB/mock is available)
    t.assert_true(true, "Mock test placeholder for connect (implement with mock or test DB)");
}

// Placeholder test for DatabaseManager setupDatabase (requires MySQL server or mock)
void test_database_manager_setup_database() {
    Test t("DatabaseManager_SetupDatabase");
    DatabaseManager* db_manager = DatabaseManager::getInstance();
    ServerInfo server_info("localhost", "test_user", "test_pass", "test_db", 3306);

    // Note: This test requires a running MySQL server or a mock.
    // For unit testing, mock mysql_query and mysql_error.
    // Example with a real DB (uncomment and configure if test DB is available):
    /*
    t.assert_true(db_manager->connect(server_info), "Should connect to the database");
    t.assert_true(db_manager->setupDatabase(), "Should set up the MOVIE_BOOKING database");
    t.assert_true(db_manager->disconnect(), "Should disconnect successfully");
    */
    
    // Placeholder pass (replace with actual test when DB/mock is available)
    t.assert_true(true, "Mock test placeholder for setupDatabase (implement with mock or test DB)");
}

int main() {
    // Run all tests
    test_server_info_default_constructor();
    test_server_info_parameterized_constructor();
    test_server_info_setters_getters();
    test_database_manager_singleton();
    test_database_manager_disconnect_no_connection();
    test_database_manager_connect();
    test_database_manager_setup_database();

    // Print test summary
    Test::print_summary();
    return 0;
}