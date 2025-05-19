#include "../include/Logger.h"

std::shared_ptr<Logger> Logger::getInstance() {
    if (!instance) {
        instance = std::shared_ptr<Logger>(new Logger());
    }
    return instance;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (!logFile.is_open()) {
        logFile.open("log.txt", std::ios::out);  // Open in write mode
    }
    if (logFile.is_open()) {
        logFile << message << std::endl;
        logFile.flush();  // Ensure immediate writing
    }
} 