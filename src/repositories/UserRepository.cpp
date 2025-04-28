#include "../../include/repositories/UserRepository.h"


Result<std::vector<User>> UserRepository::findUserById(int userId) {
    Result<std::vector<User>> result;
    std::string query = "SELECT * FROM User WHERE userID =" + std::to_string(userId) + ";";
    try{
        QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
        if (query_result.success && query_result.result) {
            MYSQL_ROW row;
            MYSQL_RES* mysqlResult = query_result.result.get();
    
            // Fetch each row and convert it into a User object
            while ((row = mysql_fetch_row(mysqlResult)) != nullptr) {
    
                int userId = std::stoi(row[0]);
                std::string username = row[1];
                std::string email = row[2];
                std::string password = row[3];
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
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();

        // Fetch each row and convert it into a User object
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
Result<User> UserRepository::save (const User& user) {
    Result<User> result;
    std::string query = "INSERT INTO User (username, password, email, phone, isAdmin) VALUES ('" +
                        user.getUsername() + "', '" +
                        user.getPassword() + "', '" +
                        user.getEmail() + "', '" +
                        user.getPhone() + "', " +
                        std::to_string(user.getIsAdmin()) + ");";
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success) {
        result.success = true;
        result.data = user;
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
    QueryResult query_result = DatabaseManager::getInstance()->executeQuery(query);
    if (query_result.success && query_result.result) {
        MYSQL_ROW row;
        MYSQL_RES* mysqlResult = query_result.result.get();
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
        result.errorMessage = query_result.error_message;
        return result;
    }
}