/** 
 * @file crawler.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-03-23
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "crawler.h"
#include "curl.h"

using namespace std;

namespace bingo 
{
namespace crawler 
{

Crawler::Crawler()
{
}

Crawler::~Crawler()
{
}

void Crawler::GetQueryList(const string& file)
{
    ifstream fin(file.c_str());
    if (fin.fail()) 
    {
        cerr << "ERROR: FAIL TO OPEN FILE " << file << endl;
        exit(1);
    }
    string query;
    while (fin >> query) 
    {
        mQueryList.insert(query);
    }
}

void Crawler::Start()
{
    for (set<string>::iterator p = mQueryList.begin(); p != mQueryList.end(); ++p) 
    {
        Download(*p);
    }
}

void Crawler::Download(const string& query)
{
    CURL* curl = curl_easy_init();   
    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.baidu.com/");
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

} // end of crawler 
} // end of bingo 
