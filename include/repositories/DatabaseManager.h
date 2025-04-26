#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>


class DatabaseManager {
private:
    static DatabaseManager* instance;
    MYSQL* conn;

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
