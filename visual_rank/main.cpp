/** 
 * @file main.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-19
 */

#include "visual_rank.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;
using namespace bingo::visualrank;
using namespace bingo::imagesimilarity;

int main(int argc, const char *argv[])
{
	ifstream in("../data/query_list");

	if (in.fail()) 
	{
		cerr << "FAIL TO OPEN FILE ../data/query_list" << endl;
		exit(1);
	}

	string query;
	ImageSimilarity* judge = new ImageSimilarity();
	VisualRank visualRank;
	while (in >> query) 
	{
		visualRank.GetVisualRank(string("../data/images/") + query + "/", judge);
		visualRank.Output(string("../data/visual_rank/") + query);
	}

	delete judge;

	return 0;
}
