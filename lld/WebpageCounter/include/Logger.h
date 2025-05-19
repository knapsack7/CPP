#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <memory>
#include <mutex>
#include <fstream>

// Logger interface
class ILogger {
public:
    virtual void log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

// Concrete Logger implementation
class Logger : public ILogger {
private:
    inline static std::shared_ptr<Logger> instance = nullptr;
    inline static std::ofstream logFile;
    inline static std::mutex logMutex;

    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;
    
public:
    static std::shared_ptr<Logger> getInstance();
    void log(const std::string& message) override;
};

#endif // LOGGER_H 