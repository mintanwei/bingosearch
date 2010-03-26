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
#include "sys/stat.h"

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


void Crawler::Start()
{
    GetQueryList();
    for (set<string>::iterator p = mQueryList.begin(); p != mQueryList.end(); ++p) 
    {
        Download(*p);
    }
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

static int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
    unsigned long sizes = size * nmemb;
    if (writerData == NULL) return 0;
    writerData->append(data, sizes);
    return sizes;
}

void Crawler::Download(const string& query)
{
    string buffer;
    CURL* curl = curl_easy_init();   

    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, "http://images.google.com.hk/images?q=ipod&start=0");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    else 
    {
        cerr << "ERROR: FAIL TO INIT CURL" << endl;
        exit(1);
    }
    cout << buffer << endl;

    string dir("data/");
    dir.append(query);
    mkdir(dir.c_str(), S_IRWXU);

    string file(dir);
}

} // end of crawler 
} // end of bingo 
