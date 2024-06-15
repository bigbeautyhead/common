#include <fmt/core.h>
#include <fmt/chrono.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "../include/log.h"

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

template<typename T>
void Logger::log(LogLevel level, const std::string& message, const T& value){
    if (level >= logLevel){
        auto now = std::time(nullptr);
        std::string levelStr = logLevelToString(level);
        std::string logmessage = fmt::format("{:%Y-%m-%d %H:%M:%S} [{}] {}", fmt::localtime(now), levelStr, message);
        if (logFile.is_open()) {
            logFile << logmessage << value << std::endl;
        }
    }
}

void Logger::debug(const std::string& message)
{
    log(LogLevel::DEBUG, message, ""); // Add an empty string as the third parameter
}
void Logger::info(const std::string& message)
{
    log(LogLevel::INFO, message, ""); // Add an empty string as the third parameter
}
void Logger::error(const std::string& message)
{
    log(LogLevel::ERROR, message, "");
}
void Logger::warning(const std::string& message)
{
    log(LogLevel::WARNING, message, "");
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