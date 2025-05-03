#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>
#include <memory>
class Logger {
public:
    enum Level { INFO, WARNING, ERROR };

    void setLogFile(const std::string& filename);        // Thiết lập file log
    void log(const std::string& message, Level level = INFO);

    static Logger* getInstance(); // Lấy instance của Logger (Singleton)
    
    Logger() = default;                                  // Constructor private
    ~Logger();
private:
    
    inline static std::unique_ptr<Logger> instance  = nullptr; // Singleton instance
    
    inline static const std::string DEFAULT_LOG_FILE = "./log.txt"; // Tên file log mặc định

    std::ofstream file;
    bool toFile = false;
    std::mutex mtx;

    std::string getTime();
    std::string levelToString(Level level);
};


#endif