#include "logger.h"
#include <iostream>
#include <ctime>

std::unique_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::instanceMutex;

Logger& Logger::getInstance() {
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (instance == nullptr) {
        instance.reset(new Logger());
    }
    return *instance;
}

void Logger::setLogFile(const std::string& filename) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (logFile.is_open()) {
        logFile.close();
    }
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + filename);
    }
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);

    auto now = std::time(nullptr);
    auto* timeInfo = std::localtime(&now);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", timeInfo);

    logFile << "[" << timeBuffer << "] " << message << std::endl;
    logFile.flush();
}
