/** 
 * @file log.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-03-27
 */

#ifndef BINGO_COMMON_LOG_H
#define BINGO_COMMON_LOG_H

#include <string>
#include <fstream>
#include <iostream>

namespace bingo 
{
namespace log 
{

class Log 
{

public:
enum LogLevel
{
    DEBUG = 0,
    WARNING = 1,
    ERROR = 2
};

public:
    Log();
    virtual ~Log();
    static void Output(const std::string& content, LogLevel logLevel);

private:
};

void Log::Output(const std::string& content, LogLevel logLevel)
{
    if (logLevel < LOG_LEVEL) 
    {
        return ;
    }
    switch (logLevel)
    {
        case DEBUG:
            std::cerr << "LOG_DEBUG: " << content << std::endl;
            break;
        case WARNING:
            std::cerr << "LOG_WARNING: " << content << std::endl;
            break;
        case ERROR:
            std::cerr << "LOG_ERROR: " << content << std::endl;
            break;
        default:
            break;
    }
}

} /* end of log */
} /* end of bingo */


#endif /* end of include guard: BINGO_COMMON_LOG_H */

