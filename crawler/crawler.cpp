/** 
 * @file crawler.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-03-23
 */

#include <fstream>
#include "log.h"
#include "common.h"
#include "crawler.h"
#include "curl.h"
#include "sys/stat.h"

using namespace std;
using namespace bingo::log;
using namespace bingo::common;

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
		Log::Output((string)("FAIL TO OPEN FILE") + file, Log::ERROR);
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
    size_t sizes = size * nmemb;
    if (writerData == NULL) return 0;
    writerData->append(data, sizes);
    return sizes;
}

void Crawler::Download(const string& query)
{
    string dir("../data/pages/");
    dir.append(query);
    mkdir(dir.c_str(), S_IRWXU);

	for (size_t i = 0; i < MAX_DOWNLOAD_PAGE; ++i) 
	{
		Download(query, i, dir);
	}
}

void Crawler::Download(const string& query, const size_t page, const string& dir)
{
	Log::Output(Common::itoa<size_t>(page) + " " + query, Log::DEBUG);
    string buffer;
    CURL* curl = curl_easy_init();   

    if (curl) 
    {
		string url("http://images.google.com.hk/images?hl=zh-CN&newwindow=1&safe=strict&tbs=isch:1&sa=N");
		url.append("&q=");
		url.append(query);
		url.append("&start=");
		url.append(Common::itoa<size_t>(page * IMAGES_PER_PAGE));
		url.append("&ndsp=");
		url.append(Common::itoa<size_t>(IMAGES_PER_PAGE));
		Log::Output(url, Log::DEBUG);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    else 
    {
		Log::Output("FAIL TO INIT CURL", Log::ERROR);
        exit(1);
    }
    string file(dir);
	file.append(1, '/');
	file.append(Common::itoa<size_t>(page));
	ofstream fout(file.c_str());
    if (fout.fail()) 
    {
        Log::Output(string("FAIL TO CREATE FILE ") + file, Log::ERROR);
        exit(1);
    }
	fout << buffer;
}

} // end of crawler 
} // end of bingo 
