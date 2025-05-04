#include "../../include/utils/Logger.h"

/**
 * @file Logger.cpp
 * @brief Implementation of the Logger class for logging messages to a file or console.
 * 
 * This file contains the implementation of the `Logger` class, which provides
 * thread-safe logging functionality with support for different log levels.
 */

/**
 * @brief Set the log file for logging messages.
 * 
 * This method sets the file where log messages will be written. If a file is already open,
 * it will be closed before opening the new file.
 * 
 * @param filename The name of the log file.
 */
void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    if (file.is_open()) file.close();

    file.open(filename, std::ios::app);
    toFile = file.is_open();
}        

/**
 * @brief Log a message with a specified log level.
 * 
 * This method logs a message to the log file if it is open, otherwise it logs to the console.
 * The log message includes a timestamp and the log level.
 * 
 * @param message The message to log.
 * @param level The log level (INFO, WARNING, ERROR).
 */
void Logger::log(const std::string& message, Level level ) {
    std::lock_guard<std::mutex> lock(mtx);

    std::string timeStr = getTime();
    std::string logMessage = "[" + timeStr + "][" + levelToString(level) + "] " + message;

    if (toFile && file.is_open()) {
        file << logMessage << std::endl;
    } else {
        std::cout << logMessage << std::endl;
    }
}

/**
 * @brief Get the singleton instance of the Logger.
 * 
 * This method ensures that only one instance of the Logger exists in the application.
 * It initializes the instance with a default log file if it does not already exist.
 * 
 * @return Pointer to the singleton Logger instance.
 */
Logger* Logger::getInstance() {
    if (Logger::instance == nullptr) {
        Logger::instance = std::make_unique<Logger>();
        Logger::instance->setLogFile(Logger::instance->DEFAULT_LOG_FILE);

    }
    return Logger::instance.get();
}

/**
 * @brief Get the current time as a formatted string.
 * 
 * This method retrieves the current system time and formats it as "YYYY-MM-DD HH:MM:SS".
 * 
 * @return The formatted time string.
 */
std::string Logger::getTime() {
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}

/**
 * @brief Convert a log level to its string representation.
 * 
 * This method maps the log level enum to its corresponding string (e.g., INFO -> "INFO").
 * 
 * @param level The log level.
 * @return The string representation of the log level.
 */
std::string Logger::levelToString(Level level) {
    switch (level) {
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

/**
 * @brief Destructor for the Logger class.
 * 
 * This method ensures that the log file is closed when the Logger instance is destroyed.
 */
Logger::~Logger() {
    if(file.is_open()) {
        file.close();
    }
}

