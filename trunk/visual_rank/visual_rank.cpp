/** 
 * @file visual_rank.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-06
 */

#include "visual_rank.h"
#include "common.h"
#include "log.h"
#include <sys/types.h>
#include <dirent.h>
#include <cstdlib>

using namespace std;
using namespace bingo::log;
using namespace bingo::common;

namespace bingo 
{
namespace visualrank 
{

VisualRank::VisualRank()
{
}

VisualRank::~VisualRank()
{
}

void VisualRank::GetVisualRank(const string& path, const ImageSimilarity* judge, 
		                       vector<double>& visualRank)
{
	size_t imageCount = GetDirItemCount(path);

	// get basic similarity matric
	for (size_t i = 0; i < imageCount; ++i) 
	{
		mMat[i][i] = -1;
		for (size_t j = i + 1; j < count; ++j) 
		{
			mMat[i][j] = mMat[j][i] = DAMPING_FACTOR * 
				judge->GetSimilarity(path + Common::itoa<size_t>(i), 
						             path + Common::itoa<size_t>(j));
		}
	}
	// normalize
	for (size_t j = 0; j < imageCount; ++j) 
	{
		double colSum = 0;
		for (size_t i = 0; i < imageCount; ++i)
		{
			colSum += mMat[i][j];
		}
		if (colSum > EPS) 
		{
			for (size_t i = 0; i < imageCount; ++i) 
			{
				mMat[i][j] /= colSum;
			}
		}
	}
	// damping factor
	for (size_t i = 0; i < imageCount; ++i) 
	{
		mMat[i][imageCount] = 1 - DAMPING_FACTOR;
	}
	for (size_t j = 0; j < imageCount; ++j) 
	{
		mMat[imageCount][j] = 0;
	}
	mMat[imageCount][imageCount] = 1;
	// gauss


}

size_t VisualRank::GetDirItemCount(const string& path)
{
	DIR* dir;
	struct dirent* dirEnt;
	size_t itemCount = 0;

	if ((dir = opendir(path.c_str())) == NULL)
	{
		Log::Output(string("CAN NOT OPEN DIR ") + path, Log::ERROR); 
		exit(1);
	}
	while (dirEnt = readdir(dir)) 
	{
		if (isdigit(dirEnt->d_name[0]))
		{
			++itemCount;
		}
	}
	closedir(dir);
	return itemCount;
}

} /* end of visualrank */
} /* end of bingo */
