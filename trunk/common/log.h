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
namespace common
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
    static void Output(const std::string& file, const std::string& content, LogLevel logLevel);

private:
};

} /* end of common */
} /* end of bingo */


#endif /* end of include guard: BINGO_COMMON_LOG_H */

