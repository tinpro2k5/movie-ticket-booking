#ifndef _LOGGER_H
#define _LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>
#include <memory>

/**
 * @file Logger.h
 * @brief Header file for the Logger class.
 * 
 * This file contains the declaration of the `Logger` class, which provides
 * thread-safe logging functionality with support for different log levels.
 */

/**
 * @class Logger
 * @brief Singleton class for logging messages to a file or console.
 * 
 * The `Logger` class provides methods to log messages with different severity levels
 * (INFO, WARNING, ERROR). It supports logging to a file or the console and ensures
 * thread safety using a mutex.
 */
class Logger {
public:
    /**
     * @enum Level
     * @brief Enumeration for log levels.
     * 
     * Defines the severity levels for log messages: INFO, WARNING, and ERROR.
     */
    enum Level { INFO, WARNING, ERROR };

    /**
     * @brief Set the log file for logging messages.
     * 
     * This method sets the file where log messages will be written. If a file is already open,
     * it will be closed before opening the new file.
     * 
     * @param filename The name of the log file.
     */
    void setLogFile(const std::string& filename);

    /**
     * @brief Log a message with a specified log level.
     * 
     * This method logs a message to the log file if it is open, otherwise it logs to the console.
     * The log message includes a timestamp and the log level.
     * 
     * @param message The message to log.
     * @param level The log level (default is INFO).
     */
    void log(const std::string& message, Level level = INFO);

    /**
     * @brief Get the singleton instance of the Logger.
     * 
     * This method ensures that only one instance of the Logger exists in the application.
     * It initializes the instance with a default log file if it does not already exist.
     * 
     * @return Pointer to the singleton Logger instance.
     */
    static Logger* getInstance();

    /**
     * @brief Default constructor.
     */
    Logger() = default;

    /**
     * @brief Destructor for the Logger class.
     * 
     * This method ensures that the log file is closed when the Logger instance is destroyed.
     */
    ~Logger();

    inline static const std::string DEFAULT_LOG_FILE = "./log.txt"; // Tên file log mặc định
private:
    inline static std::unique_ptr<Logger> instance  = nullptr; // Singleton instance
    

    std::ofstream file;
    bool toFile = false;
    std::mutex mtx;

    /**
     * @brief Get the current time as a formatted string.
     * 
     * This method retrieves the current system time and formats it as "YYYY-MM-DD HH:MM:SS".
     * 
     * @return The formatted time string.
     */
    std::string getTime();

    /**
     * @brief Convert a log level to its string representation.
     * 
     * This method maps the log level enum to its corresponding string (e.g., INFO -> "INFO").
     * 
     * @param level The log level.
     * @return The string representation of the log level.
     */
    std::string levelToString(Level level);
};

#endif