/** 
 * @file visual_rank.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-06
 */

#include "visual_rank.h"
#include "log.h"
#include "common.h"
#include <sys/types.h>
#include <dirent.h>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <algorithm>

using namespace std;
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

void VisualRank::GetVisualRank(const string& path, ImageSimilarity* judge)
{
    if (judge == NULL) 
    {
        Log::Output("visual_rank.cpp", "IMAGE SIMILARITY POINTER IS NULL", Log::ERROR);
        exit(1);
    }

	mImageCount = min((size_t)(IMAGE_PER_PATH), GetDirItemCount(path));
    if (mImageCount == 0) 
    {
        Log::Output("visual_rank.cpp", string("NO IMAGE FILE IN ") + path, Log::WARNING);
		return;
    }

    // get basic similarity matrix
    for (size_t i = 0; i < mImageCount - 1; ++i) 
    {
        mRes[i] = 0;
    }
    mRes[mImageCount - 1] = 1;

    for (size_t i = 0; i < mImageCount; ++i) 
    {
        mMat[i][i] = 0;
        for (size_t j = i + 1; j < mImageCount; ++j) 
        {
            mMat[i][j] = mMat[j][i] = DAMPING_FACTOR * 
                judge->GetSimilarity(path + Common::itoa<size_t>(i), 
                                     path + Common::itoa<size_t>(j));
        }
    }
    // normalize
    for (size_t j = 0; j < mImageCount; ++j) 
    {
        double colSum = 0;
        for (size_t i = 0; i < mImageCount; ++i)
        {
            colSum += mMat[i][j];
        }
        if (colSum > EPS) 
        {
            for (size_t i = 0; i < mImageCount; ++i) 
            {
                mMat[i][j] /= colSum;
            }
        }
    }
    for (size_t i = 0; i < mImageCount; ++i) 
    {
        mMat[i][i] = -1;
    }
    // gauss
    for (size_t j = 0; j < mImageCount; ++j) 
    {
        mMat[mImageCount - 1][j] = 1;
    }
    GaussTpivot(mImageCount);

    // for test
    for (size_t i = 0; i < mImageCount; ++i) 
    {
        for (size_t j = 0; j < mImageCount; ++j)
        {
            cout << mMat[i][j] << " ";
        }
        cout << endl;
    }
    for (size_t i = 0; i < mImageCount; ++i) 
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
        Log::Output("visual_rank.cpp", string("CAN NOT OPEN DIR ") + path, Log::WARNING); 
		return 0;
    }
    while (dirEnt = readdir(dir)) 
    {
		bool isImage = true;
		for (size_t i = 0; dirEnt->d_name[i]; ++i) 
		{
			if (!isdigit(dirEnt->d_name[i])) 
			{
				isImage = false;
				break;
			}
		}
		if (isImage) 
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
        Log::Output("visual_rank.cpp", (string)("FAIL TO WRITE FILE ") + path, Log::ERROR);
        exit(1);
    }

    for (size_t i = 0; i < mImageCount; ++i) 
    {
        out << mRes[i] << endl;
    }
}

} /* end of visualrank */
} /* end of bingo */
