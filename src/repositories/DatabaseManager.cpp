#include "repositories/DatabaseManager.h"


// @tinpro2k5 TODO: check hợp lệ đối số các hàm của ServerInfo


ServerInfo::ServerInfo() {
    host = std::getenv("DB_HOST") ? std::getenv("DB_HOST") : "localhost";
    user = std::getenv("DB_USER") ? std::getenv("DB_USER") : "root";
    password = std::getenv("DB_PASS") ? std::getenv("DB_PASS") : "";
    port = std::getenv("DB_PORT") ? std::stoi(std::getenv("DB_PORT")) : 3306;
}
ServerInfo::ServerInfo(const std::string& host, 
                        const std::string& user,
                        const std::string& password,
                        const std::string& dbname,
                        unsigned int port
                    )
{
    this->host = host;
    this->user = user;
    this->password = password;
    this->port = port;
}



void ServerInfo::setHost(const std::string& host){
    this->host = host;
}
void ServerInfo::setUser(const std::string& user) {
    this->user = user;
}
void ServerInfo::setPassword(const std::string& password) {
    this->password = password;
}

void ServerInfo::setPort(unsigned int port) {
    this->port = port;
}


std::string ServerInfo::getHost() const {
    return host;
}
std::string ServerInfo::getUser() const {
    return user;
}
std::string ServerInfo::getPassword() const {
    return password;
}

unsigned int ServerInfo::getPort() const {
    return port;
}

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
// Constructor
bool DatabaseManager::connect(const ServerInfo& server_info) {
    conn = mysql_init(0);

    if (conn == nullptr) {
        std::cerr << "MySQL initialization failed!\n";
        return false;
    }

    conn = mysql_real_connect(conn, server_info.getHost().c_str(),
                                server_info.getUser().c_str(), 
                                server_info.getPassword().c_str(),
                                server_info.DEFAULT_SYS_DB_NAME.c_str(),
                                server_info.getPort(),
                                NULL,0 
                            );

    if (conn == nullptr) {
        std::cout << "MySQL connection failed: " << mysql_error(conn) << "\n";
        return false;
    }
    std::cout << "Database connected successfully!\n";
    return true;
}

// Destructor
DatabaseManager::~DatabaseManager() {
    if (conn != nullptr) {
        this->disconnect();
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

bool DatabaseManager::disconnect() {
    if (conn != nullptr) {
        mysql_close(conn);
        conn = nullptr;
        std::cout << "Database disconnected successfully!\n";
        return true;
    }
    return false;
}
bool DatabaseManager::setupDatabase() {
    if (conn == nullptr) {
        std::cerr << "No active connection to the database.\n";
        return false;
    }
    // tạo ra và sử dụng nếu không tồn tại database: MOVIE_BOOKING
    std::string create_db_query = "CREATE DATABASE IF NOT EXISTS MOVIE_BOOKING";
    if (mysql_query(conn, create_db_query.c_str())) {
        std::cerr << "Failed to create database: " << mysql_error(conn) << "\n";
        return false;
    }
    std::cout << "Database MOVIE_BOOKING created successfully!\n";
    // sử dụng database MOVIE_BOOKING
    std::string use_db_query = "USE MOVIE_BOOKING";
    if (mysql_query(conn, use_db_query.c_str())) {
        std::cerr << "Failed to use database: " << mysql_error(conn) << "\n";
        return false;
    }
    std::cout << "Using database MOVIE_BOOKING!\n";
 
    //TODO: Tạo ra các bảng trong database MOVIE_BOOKING
    // tạo ra bảng movie nếu không tồn tại

    return true;
}
