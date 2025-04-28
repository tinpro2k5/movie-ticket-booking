#include "../../include/utils/DatabaseManager.h"


// @tinpro2k5 TODO: check hợp lệ đối số các hàm của ServerInfo

std::string CREATE_DB_QUERY = "CREATE DATABASE IF NOT EXISTS MOVIE_BOOKING";
std::string USE_DB_QUERY = "USE MOVIE_BOOKING";
std::string INIT_DB_SCRIPT = "../../sql_scripts/init_db.sql";

ServerInfo::ServerInfo() {
    host = std::getenv("DB_HOST") ? std::getenv("DB_HOST") : DEFAULT_LOCAL;
    user = std::getenv("DB_USER") ? std::getenv("DB_USER") : DEFAULT_USER;
    password = std::getenv("DB_PASS") ? std::getenv("DB_PASS") : DEFAULT_PASS;
    port = std::getenv("DB_PORT") ? std::stoi(std::getenv("DB_PORT")) : DEFAULT_PORT;
}
ServerInfo::ServerInfo(const std::string& host, 
                        const std::string& user,
                        const std::string& password,
                        unsigned int port
                    )
{
    this->host = host;
    this->user = user;
    this->password = password;
    this->port = port;
}


void ServerInfo::setHost(const std::string& host){  this->host = host;  }
void ServerInfo::setUser(const std::string& user) { this->user = user;  }
void ServerInfo::setPassword(const std::string& password) { this->password = password;  }
void ServerInfo::setPort(unsigned int port) {   this->port = port;  }

std::string ServerInfo::getHost() const {   return host;    }
std::string ServerInfo::getUser() const {   return user;    }
std::string ServerInfo::getPassword() const {   return password; }
unsigned int ServerInfo::getPort() const {  return port;    }

std::unique_ptr<DatabaseManager> DatabaseManager::instance = nullptr;
// Constructor
void DatabaseManager::connect(const ServerInfo& server_info) {
    if (conn) {
        mysql_close(conn);  // Đóng kết nối trước khi tạo mới
        conn = nullptr;
    }

    conn = mysql_init(nullptr);  // Khởi tạo kết nối
    if (conn == nullptr) {
        std::cerr << "Error initializing MySQL connection: " << mysql_error(conn) << "\n";
        throw std::runtime_error("Error initializing MySQL connection: " + std::string(mysql_error(conn)));
    }
    // Thử kết nối
    if (!mysql_real_connect(conn, 
                            server_info.getHost().c_str(),
                            server_info.getUser().c_str(),
                            server_info.getPassword().c_str(),
                            nullptr,
                            server_info.getPort(),
                            nullptr, 0)) {
        std::string err = mysql_error(conn);
        mysql_close(conn);
        conn = nullptr;
        throw std::runtime_error("mysql_real_connect() failed: " + err);
    }


    std::cout << "Database connected successfully!\n";
}


// Destructor
DatabaseManager::~DatabaseManager() {
    if (conn) {
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

void DatabaseManager::disconnect() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
        std::cout << "Database disconnected successfully!\n";
    }
}
void DatabaseManager::setupDatabase() {
    std::string error = mysql_error(conn);
    if (!conn 
        || !error.empty()
    )
    {
        std::cout << mysql_error(conn) << std::endl;
        std::cerr << "No active connection to the database.\n";
        throw std::runtime_error("No active connection to the database.");
    }
    try {
        // tạo ra và sử dụng nếu không tồn tại database: MOVIE_BOOKING

        QueryResult result = executeQuery(CREATE_DB_QUERY);
        if (!result.success) {
            result.error_message = "Failed to create database: " + result.error_message;
            throw std::runtime_error("Error creating database: " + result.error_message);
        }
        std::cout << "Database MOVIE_BOOKING has been created!\n";


        result = executeQuery(USE_DB_QUERY);
        if (!result.success) {
            result.error_message = "Failed to use database: " + result.error_message;
            throw std::runtime_error("Error using database: " + result.error_message);
        }
        std::cout << "Using database MOVIE_BOOKING!\n";

        ScriptResult script_res = executeScript(INIT_DB_SCRIPT);
        if (!script_res.success) {
            script_res.error_message = "Failed to execute script: " + script_res.error_message;
            throw std::runtime_error("Error executing script: " + script_res.error_message);
        }
        std::cout << "Database MOVIE_BOOKING has been initialized!\n";  

    }
    catch (const std::exception& e) {
        std::cerr << "Error setting up database: " << e.what() << "\n";
        throw std::runtime_error("Error setting up database. " + std::string(e.what()));
    }
  
    std::cout << "Database setup completed successfully!🚀✨\n";
}



QueryResult DatabaseManager::executeQuery(const std::string& query) {
    QueryResult result;
    if (conn == nullptr) {
        std::cerr << "No active connection to the database.\n";
        throw std::runtime_error("No active connection to the database.");
    }

    if (mysql_query(conn, query.c_str())) {
        result.success = false;
        result.error_message = mysql_error(conn);
        std::cerr << "Query execution failed: " << result.error_message << "\n";
        return result;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res) {
        result.result = std::unique_ptr<MYSQL_RES, decltype(&mysql_free_result)>(res, mysql_free_result);
        result.success = true;
    } else {
        result.affected_rows = mysql_affected_rows(conn);
        result.success = true;
    }
    return result;
}


/// TODO: xử lí các dòng trong file script (các dòng comment trong file script)

ScriptResult DatabaseManager::executeScript(const std::string& script_path) {
    ScriptResult script_result;

    if (!conn) {
        script_result.success = false;
        script_result.error_message = "No active connection.";
        return script_result;
    }

    std::ifstream script_file(script_path);
    if (!script_file.is_open()) {
        script_result.success = false;
        script_result.error_message = "Could not open script file: " + script_path;
        return script_result;
    }

    std::string script((std::istreambuf_iterator<char>(script_file)), std::istreambuf_iterator<char>());
    script_file.close();

    size_t start_pos = 0;
    size_t end_pos;
    try{

        while ((end_pos = script.find(';', start_pos)) != std::string::npos) {
            std::string query = script.substr(start_pos, end_pos - start_pos);
        start_pos = end_pos + 1;

        if (query.empty()) continue;

        QueryResult qresult;
        
        if (mysql_query(conn, query.c_str())) {
            qresult.success = false;
            qresult.error_message = mysql_error(conn);
            script_result.success = false; // Nếu 1 câu lỗi, cả script coi như lỗi
        } else {
            if (mysql_field_count(conn) > 0) {
                MYSQL_RES* raw_result = mysql_store_result(conn);
                if (raw_result) {
                    qresult.result.reset(raw_result);
                } else {
                    qresult.success = false;
                    qresult.error_message = mysql_error(conn);
                    script_result.success = false;
                }
            } else {
                qresult.affected_rows = mysql_affected_rows(conn);
            }
            if (qresult.error_message.empty()) {
                qresult.success = true;
            }
        }
        
        script_result.queries.push_back(std::move(qresult));
        }
    }
    catch (const std::exception& e) {
        script_result.success = false;
        script_result.error_message = "Error executing script: " + std::string(e.what());
    }
    catch (...) {
        script_result.success = false;
        script_result.error_message = "Unknown error occurred while executing script.";
    }

    return script_result;
}
