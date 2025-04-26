#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <memory>


const char * DATABASE_HOST = "localhost";

class DatabaseManager {
private:

    static std::unique_ptr<DatabaseManager> instance; 
    MYSQL *conn; // Kết nối MySQL

    // Private constructor: chỉ được khởi tạo từ bên trong class
    DatabaseManager();

public:
    ~DatabaseManager();

    // Không cho copy
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Truy cập thể hiện duy nhất
    static DatabaseManager* getInstance();

    // Lấy kết nối MySQL
    MYSQL* getConnection();
};

#endif // DATABASEMANAGER_H
