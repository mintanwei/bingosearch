/** 
 * @file crawler.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-03-23
 */

#ifndef BINGO_CRAWLER_CRAWLER_H
#define BINGO_CRAWLER_CRAWLER_H

#include <set>
#include <string>

namespace bingo 
{
namespace crawler 
{

class Crawler 
{
public:
    Crawler();
    virtual ~Crawler();
    void GetQueryList(const std::string& file = "./query_list");
    void Start();
    
private:
    void Download(const std::string& query);
    std::set<std::string> mQueryList;
};

} // end of crawler 
} // end of bingo 

#endif // end of include guard: BINGO_CRAWLER_CRAWLER_H 
