#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>
#include <chrono>
#include <string_view>

#define PRINT(x) std::cout << x << std::endl;

namespace Core {

class FileLogger
{
public:
    enum class LogLevel{
        INFO,
        WARNING,
        ERROR
    };
    std::string TAG = "FILELOGGER";
    std::string m_FileName;
    LogLevel m_LogLevel;
public:
    ~FileLogger(){
        LOG(LogLevel::INFO, TAG, "Logger file closed");
        FILEDeleter();
    };
    FileLogger(const std::string& fileName)
        : m_FileName(fileName)
    {
        LOG(LogLevel::INFO, TAG, "Load logger file");
    };
    void LOG(const std::string& message)
    {
        LOG(LogLevel::INFO, "", message);
    };

    void LOG(const LogLevel logLevel, const std::string& TAG, const std::string& message)
    {
        std::string levelStr;

        switch (logLevel)
        {
        case LogLevel::ERROR:
            levelStr = "[ERROR]";
            break;
        case LogLevel::INFO:
            levelStr = "[INFO]";
            break;
        case LogLevel::WARNING:
            levelStr = "[WARNING]";
            break;
        default:
            levelStr = "";
            break;
        }

        // Get the current system time
        auto currentTime = std::chrono::system_clock::now();
        // Convert the time to a time_t object
        auto time = std::chrono::system_clock::to_time_t(currentTime);
        // Convert the time_t to a string representation
        char timeString[100];
        std::strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S.%s", std::localtime(&time)); // ISO 8601 https://en.cppreference.com/w/c/chrono/strftime

        std::string _message;
        if(TAG!=""){
            _message = "[" + static_cast<std::string>(timeString) + "]" + levelStr + "[" + TAG + "]" + message+"\n";
        }else{
            _message = "[" + static_cast<std::string>(timeString) + "]" + levelStr +  message+"\n";
        }
        PRINT(_message);
        //Create a smart pointer with custom deleter
        std::shared_ptr<FILE> file(std::fopen(this->m_FileName.c_str(),"a"),FILEDeleter() );
        if(!file){
            std::cerr << "Failed to open the file." << std::endl;
            return;
        }
        std::fprintf( file.get(),"%s", _message.c_str() );
    };

    struct FILEDeleter{
        void operator()(FILE *pFile){
            if(pFile){
                fclose(pFile);
                //print("File close.");
            }
        }
    };
};

}
