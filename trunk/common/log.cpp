/** 
 * @file log.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-05-09
 */

#include "log.h"

namespace bingo 
{
namespace common 
{

void Log::Output(const std::string& file, const std::string& content, LogLevel logLevel)
{
    if (logLevel < LOG_LEVEL) 
    {
        return ;
    }
    switch (logLevel)
    {
        case DEBUG:
            std::cerr << "LOG_DEBUG: " << file << " : " << content << std::endl;
            break;
        case WARNING:
            std::cerr << "LOG_WARNING: " << file << " : " << content << std::endl;
            break;
        case ERROR:
            std::cerr << "LOG_ERROR: " << file << " : " <<  content << std::endl;
            break;
        default:
            break;
    }
}

} /* end of common */
} /* end of bingo */
