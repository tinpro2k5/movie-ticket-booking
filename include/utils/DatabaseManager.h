#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <mysql/mysql.h>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

/*
Khi return, compiler sẽ tự optimize bằng kỹ thuật gọi là Return Value Optimization (RVO):
Không thực sự copy memory.
➡️  an toàn.


🛡️ Lưu ý thêm 
Không return con trỏ thô (ScriptResult*) nếu không cần thiết.
Không return reference (ScriptResult&) từ local variable → sẽ crash (vượt scope).
Luôn return bằng giá trị (ScriptResult), để C++ tự lo move optimization.

*/

struct QueryResult {
    bool success;
    std::unique_ptr<MYSQL_RES, void(*)(MYSQL_RES*)> result; // Nếu SELECT
    my_ulonglong affected_rows;                             // Nếu INSERT/UPDATE/DELETE
    std::string error_message;                              // Nếu lỗi

    QueryResult() 
        : success(false), result(nullptr, mysql_free_result), affected_rows(0) {}
};

struct ScriptResult {
    bool success;  // Cả script thành công hay không
    std::vector<QueryResult> queries; // Kết quả từng câu lệnh
    std::string error_message; // Lỗi tổng nếu có

    ScriptResult() : success(true) {}
};


class ServerInfo{
    private:
    std::string host;
    std::string user;
    std::string password;
    unsigned int port;
public:
    inline static std::string DEFAULT_LOCAL = "localhost";
    inline static std::string DEFAULT_USER = "root";
    inline static std::string DEFAULT_PASS = "rootpassword";
    inline static unsigned int DEFAULT_PORT = 3306;
    ServerInfo();
    ServerInfo(const std::string& host, const std::string& user, const std::string& password, unsigned int port);
    
    
    
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

    QueryResult executeQuery(const std::string& query);
    ScriptResult executeScript(const std::string& script_path);
};


#endif // DATABASEMANAGER_H
