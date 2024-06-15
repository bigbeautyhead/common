#pragma once

#include <string>
#include <fstream> 
#include <filesystem>
#include <stdexcept>

#ifndef LOG_H
#define LOG_H

enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

class Logger {

private:
    LogLevel logLevel;
    std::ofstream logFile;

    std::string logLevelToString(LogLevel level);
    void openLogFile();
    std::string getCurrentDate();
    void createLogDirectory();
public:
    Logger(LogLevel level = LogLevel::INFO);
    ~Logger();

    void setLogLevel(LogLevel level);
    template<typename T>
    void log(LogLevel level, const std::string& message, const T& value = T());
    void debug(const std::string& message);
    void info(const std::string& message);
    void error(const std::string& message);
    void warning(const std::string& message);
};

#endif  // LOG_H