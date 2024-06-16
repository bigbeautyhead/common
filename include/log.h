
#ifndef LOG_H
#define LOG_H

#pragma once

#include <string>
#include <fstream> 
#include <filesystem>
#include <stdexcept>
#include <fmt/core.h>
#include <fmt/chrono.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

enum class LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR
};

#define LOG_DEBUG(logger, message, ...) logger.debug(message, ##__VA_ARGS__)
#define LOG_INFO(logger, message, ...) logger.info(message, ##__VA_ARGS__)
#define LOG_ERROR(logger, message, ...) logger.error(message, ##__VA_ARGS__)
#define LOG_WARNING(logger, message, ...) logger.warning(message, ##__VA_ARGS__)

class Logger {

private:
    LogLevel logLevel;
    std::ofstream logFile;

    std::string logLevelToString(LogLevel level);
    void openLogFile();
    std::string getCurrentDate();
    void createLogDirectory();
    void printdate(LogLevel level, const std::string& message);
public:
    Logger(LogLevel level = LogLevel::INFO);
    ~Logger();

    void setLogLevel(LogLevel level);
    template<typename T>
    void log(LogLevel level, const std::string& message, const T& value);
    template<typename T, typename... Args>
    void logs(LogLevel level, const std::string& message, const T& value, const Args&... args);
    void logs(LogLevel level, const std::string& message) {
        if (logFile.is_open()) {
            logFile <<std::endl;
        }
    } // 基础模板终止递归

    // Append all values to the log message
    template<typename T>
    void appendValues(std::ostringstream& logmessage, const T& value);

    template<typename T, typename... Args>
    void appendValues(std::ostringstream& logmessage, const T& value, const Args&... args);

    template<typename... Args>
    void debug(const std::string& message, Args... args);

    template<typename... Args>
    void info(const std::string& message, Args... args);

    template<typename... Args>
    void error(const std::string& message, Args... args);

    template<typename... Args>
    void warning(const std::string& message, Args... args);
};


Logger::Logger(LogLevel level) : logLevel(level) {
    createLogDirectory();
    openLogFile();
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::logLevelToString(LogLevel level)
{
    switch (level)
    {
    case LogLevel::DEBUG :
        return "DEBUG";
    case LogLevel::INFO :
        return "INFO";
    case LogLevel::WARNING :
        return "WARNING";
    case LogLevel::ERROR :
        return "ERROR";
    default:
        return "UNKNOW";
    }
}

void Logger::setLogLevel(LogLevel level){
        logLevel = level;
    }


// Helper function to append values to the log message
template<typename T>
void Logger::appendValues(std::ostringstream& logmessage, const T& value) {
    logmessage << " " << value;
}

template<typename T, typename... Args>
void Logger::appendValues(std::ostringstream& logmessage, const T& value, const Args&... args) {
    logmessage << " " << value;
    appendValues(logmessage, args...);
}

template<typename T>
void Logger::log(LogLevel level, const std::string& message, const T& value){
    if (level >= logLevel){
        std::ostringstream values;
        appendValues(values, value);
        if (logFile.is_open()) {
            logFile << values.str();
        }
    }
}

template<typename T, typename... Args>
void Logger::logs(LogLevel level, const std::string& message, const T& value, const Args&... args) {
    log(level, message, value);
    logs(level, message, args...);
}

void Logger::printdate(LogLevel level, const std::string& message)
{
    auto now = std::time(nullptr);
    std::string levelStr = logLevelToString(level);
    std::ostringstream logmessage;
    logmessage << fmt::format("{:%Y-%m-%d %H:%M:%S} [{}] {}", fmt::localtime(now), levelStr, message);
    if (logFile.is_open()) {
        logFile << logmessage.str();
    }
}

template<typename... Args>
void Logger::debug(const std::string& message, Args... args)
{
    printdate(LogLevel::DEBUG, message);
    logs(LogLevel::DEBUG, message, args...); // Add an empty string as the third parameter
}

template <typename... Args>
void Logger::info(const std::string& message, Args... args)
{
    printdate(LogLevel::INFO, message);
    logs(LogLevel::INFO, message, args...); // Add an empty string as the third parameter
}

template <typename... Args>
void Logger::error(const std::string& message, Args... args)
{
    printdate(LogLevel::ERROR, message);
    logs(LogLevel::ERROR, message, args...); // Add an empty string as the third parameter
}

template <typename... Args>
void Logger::warning(const std::string& message, Args... args)
{
    printdate(LogLevel::WARNING, message);
    logs(LogLevel::WARNING, message, args...); // Add an empty string as the third parameter
}

std::string Logger::getCurrentDate() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d");
    return oss.str();
}

void Logger::openLogFile() {
    std::string filename = "log/log_" + getCurrentDate() + ".txt";
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
}

void Logger::createLogDirectory() {
    if (!std::filesystem::exists("log")) {
        std::filesystem::create_directory("log");
    }
}

#endif  // LOG_H