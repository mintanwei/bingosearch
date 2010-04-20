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
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;
using namespace bingo::log;
using namespace bingo::common;
using namespace bingo::imagesimilarity;

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

void VisualRank::GetVisualRank(const string& path, const ImageSimilarity* judge)
{
	if (judge == NULL) 
	{
		Log::Output("IMAGE SIMILARITY POINTER IS NULL", Log::ERROR);
		exit(1);
	}

	imageCount = GetDirItemCount(path);

	if (imageCount == 0) 
	{
		Log::Output(string("NO IMAGE FILE IN ") + path, Log::ERROR);
		exit(1);
	}

	// get basic similarity matrix
	for (size_t i = 0; i < imageCount - 1; ++i) 
	{
		mRes[i] = 0;
	}
	mRes[imageCount - 1] = 1;

	for (size_t i = 0; i < imageCount; ++i) 
	{
		mMat[i][i] = 0;
		for (size_t j = i + 1; j < imageCount; ++j) 
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
	for (size_t i = 0; i < imageCount; ++i) 
	{
		mMat[i][i] = -1;
	}
	// gauss
	for (size_t j = 0; j < imageCount; ++j) 
	{
		mMat[imageCount - 1][j] = 1;
	}
	GaussTpivot(imageCount);

	// for test
	for (size_t i = 0; i < imageCount; ++i) 
	{
		for	(size_t j = 0; j < imageCount; ++j)
		{
			cout << mMat[i][j] << " ";
		}
		cout << endl;
	}
	for (size_t i = 0; i < imageCount; ++i) 
	{
		cout << i << " " << mRes[i] << endl;
	}
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

bool VisualRank::GaussTpivot(size_t n) 
{
	int i, j, k, row, col, index[IMAGE_PER_PATH];
	double maxp, t;

	for (i = 0; i < n; i++) 
	{
		index[i] = i;
	}
	for (k = 0; k < n; k++) 
	{
		for (maxp = 0, i = k; i < n; i++) 
		{
			for (j = k; j < n; j++) 
			{
				if (fabs(mMat[i][j]) > fabs(maxp)) 
				{
					maxp = mMat[row = i][col = j];
				}
			}
		}
		if (fabs(maxp) < EPS) 
		{
			return false;
		}
		if (col != k) 
		{
			for (i = 0; i < n; i++) 
			{
				t = mMat[i][col];
				mMat[i][col] = mMat[i][k];
				mMat[i][k] = t;
			}
			j = index[col];
			index[col] = index[k];
			index[k] = j;
		}
		if (row != k) 
		{
			for (j = k; j < n; j++) 
			{
				t = mMat[k][j];
				mMat[k][j] = mMat[row][j];
				mMat[row][j] = t;
			}
			t = mRes[k];
			mRes[k] = mRes[row];
			mRes[row] = t;
		}
		for (j = k + 1; j < n; j++) 
		{
			mMat[k][j] /= maxp;
			for (i = k + 1; i < n; i++) 
			{
				mMat[i][j] -= mMat[i][k] * mMat[k][j];
			}
		}
		mRes[k] /= maxp;
		for (i = k + 1; i < n; i++) 
		{
			mRes[i] -= mRes[k] * mMat[i][k];
		}
	}
	for (i = n - 1; i >= 0; i--) 
	{
		for (j = i + 1; j < n; j++) 
		{
			mRes[i] -= mMat[i][j] * mRes[j];
		}
	}
	for (k = 0; k < n; k++) 
	{
		mMat[0][index[k]] = mRes[k];
	}
	for (k = 0; k < n; k++) 
	{
		mRes[k] = mMat[0][k];
	}
	return true;
}

void VisualRank::Output(const string& path)
{
	ofstream out(path.c_str());
	
	if (out.fail()) 
	{
		Log::Output((string)("FAIL TO WRITE FILE ") + path, Log::ERROR);
		exit(1);
	}

	for (size_t i = 0; i < imageCount; ++i) 
	{
		out << mRes[i] << endl;
	}
}

} /* end of visualrank */
} /* end of bingo */
