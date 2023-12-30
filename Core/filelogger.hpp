#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <chrono>
#include <map>

#define PRINT(x) std::cout << x << std::endl;

namespace Core {
class Logger
{
public:
    enum class Level
    {
        INFO,
        WARNING,
        ERROR
    };

public:
    static Logger &Instance()
    {
        static Logger *s_instance = new Logger;
        return *s_instance;
    }

    inline void LOG(const std::string message)
    {
        LOG(Level::INFO, "", message);
    };

    inline void LOG(const Level logLevel, const std::string &TAG, const std::string message)
    {
        // Create a smart pointer with custom deleter
        std::shared_ptr<FILE> file(std::fopen(this->m_FileName.c_str(), "a"), FILEDeleter());
        if (!file)
        {
            std::cerr << "Failed to open the file." << std::endl;
            return;
        }
        // Get the current system time
        auto currentTime = std::chrono::system_clock::now();
        // Convert the time to a time_t object
        auto time = std::chrono::system_clock::to_time_t(currentTime);
        // Convert the time_t to a string representation
        char timeString[100];
        std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S.%s", std::localtime(&time)); // ISO 8601 https://en.cppreference.com/w/c/chrono/strftime
        // String builder
        std::string _message;
        if (TAG != "")
        {
            _message = "[" + static_cast<std::string>(timeString) + "][" + levelStr[logLevel] + "][" + TAG + "]" + message + "\n";
        }
        else
        {
            _message = "[" + static_cast<std::string>(timeString) + "][" + levelStr[logLevel] + "]" + message + "\n";
        }
        // Flush message to file
        std::fprintf(file.get(), "%s", _message.c_str());
    };

    inline void SetFileName(const std::string &_filename) { m_FileName = _filename; };
    inline std::string GetFileName() const { return m_FileName; };

private:
    explicit Logger(){};
    ~Logger(){};
    // Custom deleter
    struct FILEDeleter
    {
        void operator()(FILE *pFile)
        {
            if (pFile)
            {
                fclose(pFile);
            }
        }
    };
    // Prevent copying
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    std::string m_TAG = "Logger";
    std::string m_FileName;
    Level m_LogLevel;

    std::map<Level, std::string> levelStr = {
        {Level::INFO, "INFO"},
        {Level::WARNING, "WARNING"},
        {Level::ERROR, "ERROR"},
        };
};

};//namespace Core
