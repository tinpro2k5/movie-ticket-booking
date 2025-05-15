#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "../../include/utils/Logger.h"

/**
 * @file DatabaseManager.h
 * @brief Header file for managing database connections and operations.
 * 
 * This file contains the declarations for the `DatabaseManager` and `ServerInfo` classes,
 * as well as supporting structures for query and script results.
 */

/**
 * @struct QueryResult
 * @brief Represents the result of a single SQL query.
 * 
 * Contains information about the success of the query, the result set (if applicable),
 * the number of affected rows, and any error messages.
 */
struct QueryResult {
    bool success;
    std::unique_ptr<MYSQL_RES, void(*)(MYSQL_RES*)> result; // Nếu SELECT
    my_ulonglong affected_rows;                             // Nếu INSERT/UPDATE/DELETE
    std::string error_message;                              // Nếu lỗi

    QueryResult() 
        : success(false), result(nullptr, mysql_free_result), affected_rows(0) {}
};

/**
 * @struct ScriptResult
 * @brief Represents the result of executing a SQL script.
 * 
 * Contains information about the overall success of the script, the results of individual queries,
 * and any error messages.
 */
struct ScriptResult {
    bool success;  // Cả script thành công hay không
    std::vector<QueryResult> queries; // Kết quả từng câu lệnh
    std::string error_message; // Lỗi tổng nếu có

    ScriptResult() : success(true) {}
};

/**
 * @class ServerInfo
 * @brief Stores information about the database server.
 * 
 * This class encapsulates the host, user, password, and port required to connect to a database server.
 */
class ServerInfo {
private:
    std::string host;
    std::string user;
    std::string password;
    unsigned int port;
public:
    /**
     * @brief Default values for server connection.
     */
    inline static std::string DEFAULT_LOCAL = "127.0.0.1"; ///< Default host address.
    inline static std::string DEFAULT_USER = "root";       ///< Default username.
    inline static std::string DEFAULT_PASS = "rootpassword"; ///< Default password.
    inline static unsigned int DEFAULT_PORT = 3306;        ///< Default port number.

    /**
     * @brief Default constructor.
     */
    ServerInfo();

    /**
     * @brief Parameterized constructor.
     * @param host The host address.
     * @param user The username.
     * @param password The password.
     * @param port The port number.
     */
    ServerInfo(const std::string& host, const std::string& user, const std::string& password, unsigned int port);

    /**
     * @brief Set the host address.
     * @param host The host address.
     */
    void setHost(const std::string& host);

    /**
     * @brief Set the username.
     * @param user The username.
     */
    void setUser(const std::string& user);

    /**
     * @brief Set the password.
     * @param password The password.
     */
    void setPassword(const std::string& password);

    /**
     * @brief Set the port number.
     * @param port The port number.
     */
    void setPort(unsigned int port);

    /**
     * @brief Get the host address.
     * @return The host address.
     */
    std::string getHost() const;

    /**
     * @brief Get the username.
     * @return The username.
     */
    std::string getUser() const;

    /**
     * @brief Get the password.
     * @return The password.
     */
    std::string getPassword() const;

    /**
     * @brief Get the port number.
     * @return The port number.
     */
    unsigned int getPort() const;
};

/**
 * @class DatabaseManager
 * @brief Singleton class for managing database connections and executing queries.
 * 
 * This class provides methods to connect to a database, execute queries, and manage the connection lifecycle.
 */
class DatabaseManager {
private:
    static std::unique_ptr<DatabaseManager> instance; ///< Singleton instance.
    MYSQL *conn; ///< MySQL connection object.

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    DatabaseManager() {
        conn = nullptr;
    }

public:
    /**
     * @brief Destructor to clean up resources.
     */
    ~DatabaseManager();

    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    DatabaseManager(const DatabaseManager&) = delete;

    /**
     * @brief Deleted assignment operator to prevent copying.
     */
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    /**
     * @brief Get the singleton instance of the DatabaseManager.
     * @return Pointer to the singleton instance.
     */
    static DatabaseManager* getInstance();

    /**
     * @brief Set up the database by executing initialization scripts.
     */
    void setupDatabase(const std::string& INIT_DB_SCRIPT);

    /**
     * @brief Connect to the database server.
     * @param server_info The server information required for connection.
     */
    void connect(const ServerInfo& server_info);

    /**
     * @brief Disconnect from the database server.
     */
    void disconnect();

    /**
     * @brief Check if the database is connected.
     * @return True if connected, false otherwise.
     */
    bool isConnected() const {
        return conn != nullptr;
    }

    /**
     * @brief Execute a single SQL query.
     * @param query The SQL query string.
     * @return The result of the query.
     */
    QueryResult executeQuery(const std::string& query);

    /**
     * @brief Execute a SQL script from a file.
     * @param script_path The path to the SQL script file.
     * @return The result of the script execution.
     */
    ScriptResult executeScript(const std::string& script_path);

    /**
     * @brief Get the MySQL connection object.
     * @return Pointer to the MySQL connection object.
     */
    MYSQL* getConnection();
};

#endif // DATABASEMANAGER_H
