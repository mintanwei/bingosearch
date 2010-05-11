/** 
 * @file main.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-19
 */

#include "log.h"
#include "visual_rank.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
using namespace bingo::common;
using namespace bingo::visualrank;

int main(int argc, const char *argv[])
{
    ifstream in("../data/query_list");

    if (in.fail()) 
    {
		Log::Output("visual_rank main.cpp : FAIL TO OPEN FILE ../data/query_list", Log::ERROR);
        exit(1);
    }

    string query;
    VisualRank visualRank;

    ImageSimilarity* judge = new ImageSimilarity();
	ImageSimilarity* judgeSift = new ImageSimilaritySift();

    while (getline(in, query)) 
    {
        visualRank.GetVisualRank(string("../data/images/") + query + "/", judge);
        visualRank.Output(string("../data/visual_rank/") + query);
        visualRank.GetVisualRank(string("../data/images/") + query + "/", judgeSift);
        visualRank.Output(string("../data/visual_rank_sift/") + query);
    }

    delete judge;
    delete judgeSift;

    return 0;
}
