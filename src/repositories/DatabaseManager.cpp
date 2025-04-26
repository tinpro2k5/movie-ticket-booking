#include "repositories/DatabaseManager.h"


std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
// Constructor
DatabaseManager::DatabaseManager() {
    conn = mysql_init(0);

    if (conn == nullptr) {
        std::cerr << "MySQL initialization failed!\n";
        exit(1); // Lỗi nặng, thoát luôn
    }

    // to do
    conn = mysql_real_connect(conn, "localhost", "root", "", "cpp_movieticketbookingsystem", 0, NULL, 0);

    if (conn == nullptr) {
        std::cout << "MySQL connection failed: " << mysql_error(conn) << "\n";
        exit(1);
    }
    std::cout << "Database connected successfully!\n";
}

// Destructor
DatabaseManager::~DatabaseManager() {
    if (conn != nullptr) {
        mysql_close(conn);
        conn = nullptr;
        std::cout << "Database connection closed.\n"; 
    }
}

// Singleton Instance
DatabaseManager* DatabaseManager::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<DatabaseManager>(new DatabaseManager());
    }
    return instance.get();
}

// Getter Connection
MYSQL* DatabaseManager::getConnection() {
    return conn;
}
