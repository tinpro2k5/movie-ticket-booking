#include "../../include/utils/Logger.h"


void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(mtx);
    if (file.is_open()) file.close();

    file.open(filename, std::ios::app);
    toFile = file.is_open();
}        
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

Logger* Logger::getInstance() {
    if (Logger::instance == nullptr) {
        Logger::instance = std::make_unique<Logger>();
        Logger::instance->setLogFile(Logger::instance->DEFAULT_LOG_FILE);

    }
    return Logger::instance.get();
}

std::string Logger::getTime() {
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}
std::string Logger::levelToString(Level level) {
    switch (level) {
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}


Logger::~Logger() {
    if(file.is_open()) {
        file.close();
    }
}

