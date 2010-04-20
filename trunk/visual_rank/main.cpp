/** 
 * @file main.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-19
 */

#include "visual_rank.h"
#include <fstream>

using namespace bingo::visualrank;
using namespace bingo::imagesimilarity;

int main(int argc, const char *argv[])
{
	ImageSimilarity* judge = new ImageSimilarity();
	VisualRank visualRank;

	visualRank.GetVisualRank("../data/images/camera/", judge);
	visualRank.Output("../data/visual_rank/camera");

	delete judge;

	return 0;
}
