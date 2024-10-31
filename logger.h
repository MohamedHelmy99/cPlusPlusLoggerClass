#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <memory>

class Logger {
public:

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance();
    void log(const std::string& message);
    void setLogFile(const std::string& filename);

private:
    Logger() = default;
    std::ofstream logFile;
    std::mutex logMutex;
    static std::unique_ptr<Logger> instance;
    static std::mutex instanceMutex;
}; 