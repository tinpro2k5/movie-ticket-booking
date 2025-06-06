#include "../../include/repositories/UserRepository.h"


Result<std::vector<User>> UserRepository::findUserById(int userId) {
    Result<std::vector<User>> result;
    std::string query = "SELECT * FROM User WHERE userID =" + std::to_string(userId) + ";";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);
    try{
        QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
        if (query_result.success && query_result.result) {
            MYSQL_ROW row;
            MYSQL_RES* mysqlResult = query_result.result.get();
    
            Logger::getInstance()->log("Parsing query result", Logger::Level::INFO);
            while ((row = mysql_fetch_row(mysqlResult)) != nullptr) {
    
                int userId = std::stoi(row[0]);
                std::string username = row[1];
                std::string password = row[2];
                std::string email = row[3];
                std::string phone = row[4];
                bool isAdmin = std::stoi(row[5]);
                
                result.data.push_back(User(userId, username, password, email, phone, isAdmin));
            }
    
            return Result<std::vector<User>>(true, result.data, "");
        } else {
            return Result<std::vector<User>>(false, {}, query_result.error_message);
        }

    }
    catch (const std::exception& e) {
        result.success = false;
        result.error_message = e.what();
        return result;
    }
    catch (...) {
        result.success = false;
        result.error_message = "Unknown error occurred";
        return result;

    }
}
Result<std::vector<User>> UserRepository::findUserByUsername(const std::string& username) {
    Result<std::vector<User>> result;
    std::string query = "SELECT * FROM User WHERE username ='" + username + "';";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();

        Logger::getInstance()->log("Parsing query result", Logger::Level::INFO);
        while ((row = mysql_fetch_row(mysqlResult)) != nullptr) {

            int userId = std::stoi(row[0]);
            std::string username = row[1];
            std::string password = row[2];
            std::string email = row[3];
            std::string phone = row[4];
            bool isAdmin = std::stoi(row[5]);

            result.data.push_back(User(userId, username, password, email, phone, isAdmin));
        }

        return Result<std::vector<User>>(true, result.data);
    } else {
        return Result<std::vector<User>>(false, {}, query_result.error_message);
    }
}
Result<int> UserRepository::create (const User& user) {
    Result<int> result;
    std::string query = "INSERT INTO User (username, password, email, phone, isAdmin) VALUES ('" +
                        user.getUsername() + "', '" +
                        user.getPassword() + "', '" +
                        user.getEmail() + "', '" +
                        user.getPhone() + "', " +
                        std::to_string(user.getIsAdmin()) + ");";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success) {
        result.success = true;
        result.data = true; // Account created successfully
        return result;
    } else {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

}

Result<bool> UserRepository::checkExistAccount(const std::string& username, const std::string& email) {
    Result<bool> result;
    std::string query = "SELECT * FROM User WHERE username ='" + username + "' OR email ='" + email + "';";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);
    
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();
        Logger::getInstance()->log("Parsing query result", Logger::Level::INFO);
        // Check if any row exists
        if ((row = mysql_fetch_row(mysqlResult)) != nullptr) {
            result.success = true;
            result.data = true; // Account exists
            return result;
        } else {
            result.success = true;
            result.data = false; // Account does not exist
            return result;
        }
    } else {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }
}


 Result<int> UserRepository::existAdminUser() {
    Result<int> result;
    std::string query = "SELECT * FROM User WHERE isAdmin = 1;";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();

        Logger::getInstance()->log("Parsing query result", Logger::Level::INFO);
        if ((row = mysql_fetch_row(mysqlResult)) != nullptr) {
            int userId = std::stoi(row[0]);
            result.success = true;
            result.data = userId; // Admin user exists
            return result;
        } else {
            result.success = true;
            result.data = -1; // No admin user found
            result.error_message = "No admin user found";
            return result;
        }
    } else {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

 }


 Result<bool> UserRepository::remove(std::string username) {
    Result<bool> result;
    std::string query = "DELETE FROM User WHERE username ='" + username + "';";
    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success) {
        result.success = true;
        result.data = true;
        return result;
    } else {
        result.success = false;
        result.error_message = query_result.error_message;
        return result;
    }

 }

 Result<std::vector<User>> UserRepository::findUserHavingShowTime(const ShowTime& showtime) {
    Result<std::vector<User>> result;
    std::string query = "SELECT u.* FROM User u JOIN Ticket t ON u.userID = t.userID where t.roomID = " + std::to_string(showtime.getRoomId()) +
                        " AND t.theaterID = " + std::to_string(showtime.getTheaterId()) +
                        " AND t.showDateTime = '" + showtime.getShowTime() + "';";

    Logger::getInstance()->log("Executing query: " + query, Logger::Level::INFO);

    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();

        Logger::getInstance()->log("Parsing query result", Logger::Level::INFO);
        while ((row = mysql_fetch_row(mysqlResult)) != nullptr) {
            int userId = std::stoi(row[0]);
            std::string username = row[1];
            std::string password = row[2];
            std::string email = row[3];
            std::string phone = row[4];
            bool isAdmin = std::stoi(row[5]);

            result.data.push_back(User(userId, username, password, email, phone, isAdmin));
        }

        return Result<std::vector<User>>(true, result.data);
    } else {
        return Result<std::vector<User>>(false, {}, query_result.error_message);
    }
}