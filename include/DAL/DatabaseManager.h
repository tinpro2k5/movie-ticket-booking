#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>

class ServerInfo{
private:
std::string host;
std::string user;
std::string password;
unsigned int port;
public:
    std::string DEFAULT_SYS_DB_NAME = "mysql";
    ServerInfo();
    ServerInfo(const std::string& host, const std::string& user, const std::string& password, const std::string& dbname, unsigned int port);

    

    void setHost(const std::string& host);
    void setUser(const std::string& user);
    void setPassword(const std::string& password);
    void setPort(unsigned int port);
    

    std::string getHost() const;
    std::string getUser() const;
    std::string getPassword() const;
    unsigned int getPort() const;

};

class DatabaseManager {
private:

    static std::unique_ptr<DatabaseManager> instance; 
    MYSQL *conn; // Kết nối MySQL

    // Private constructor: chỉ được khởi tạo từ bên trong class
    DatabaseManager(){conn = nullptr;}   
public:
    void setupDatabase();
    void connect(const ServerInfo& server_info);
    void disconnect();
    ~DatabaseManager();

    // Không cho copy
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    // Truy cập thể hiện duy nhất
    static DatabaseManager* getInstance();

    // Lấy kết nối MySQL
    MYSQL* getConnection();


    bool isConnected() const {
        return conn != nullptr;
    }

    // TODO ngày mai 🐹🐴🐵
    int excuteQuery(const std::string& query);
    int excuteScript(const std::string& script);

};



#endif // DATABASEMANAGER_H
