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
    void Start();
    
private:
    static const size_t IMAGES_PER_PAGE = 21;
    static const size_t MAX_DOWNLOAD_PAGE = 50;
    void GetQueryList(const std::string& file = "../data/query_list");
    void Download(const std::string& query);
	void Download(const std::string& query, const size_t page, const std::string& dir);

private:
    std::set<std::string> mQueryList;
};

} // end of crawler 
} // end of bingo 

#endif // end of include guard: BINGO_CRAWLER_CRAWLER_H 
