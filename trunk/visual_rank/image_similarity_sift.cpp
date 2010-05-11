/** 
 * @file image_similarity_sift.cpp
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-05-09
 */

#include "log.h"
#include "image_similarity_sift.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;
using namespace bingo::common;

namespace bingo 
{
namespace visualrank 
{

ImageSimilaritySift::ImageSimilaritySift()
{
}

ImageSimilaritySift::~ImageSimilaritySift()
{
}

size_t ImageSimilaritySift::GetDis(const vector<int>& va, const vector<int>& vb)
{
	size_t ret = 0;
	for (size_t i = 0; i < 128; ++i)
	{
		ret += (va[i] - vb[i]) * (va[i] - vb[i]);
	}
	return ret;
}

double ImageSimilaritySift::GetSimilarity(const string& fileA, const string& fileB) 
{
	ifstream in1(fileA.c_str());
	if (in1.fail()) 
	{
		Log::Output((string)("visual_rank image_similarity_sift.cpp : FAIL TO OPEN ") + fileA, Log::ERROR);
		exit(1);
	}
	ifstream in2(fileB.c_str());
	if (in2.fail()) 
	{
		Log::Output((string)("visual_rank image_similarity_sift.cpp : FAIL TO OPEN ") + fileB, Log::ERROR);
		exit(1);
	}

	string pgmA(fileA);
	pgmA.append(".pgm");
	if (mFileSet.find(fileA) == mFileSet.end()) 
	{
		system(((string)("convert ") + fileA + " " + pgmA).c_str());
		system(((string)("../third_party/siftpp/sift ") + pgmA).c_str());
		mFileSet.insert(fileA);
	}
	string pgmB(fileB);
	pgmB.append(".pgm");
	if (mFileSet.find(fileB) == mFileSet.end()) 
	{
		system(((string)("convert ") + fileB + " " + pgmB).c_str());
		system(((string)("../third_party/siftpp/sift ") + pgmB).c_str());
		mFileSet.insert(fileB);
	}

	string keyA(fileA);
	keyA.append(".key");
	ifstream inA(keyA.c_str());
	if (inA.fail()) 
	{
		Log::Output((string)("visual_rank image_similarity_sift.cpp : FAIL TO OPEN ") + keyA, Log::ERROR);
		exit(1);
	}
	string keyB(fileB);
	keyB.append(".key");
	ifstream inB(keyB.c_str());
	if (inB.fail()) 
	{
		Log::Output((string)("visual_rank image_similarity_sift.cpp : FAIL TO OPEN ") + keyB, Log::ERROR);
		exit(1);
	}

	string line;
	int thisOne;
	vector<vector<int> > va;
	vector<vector<int> > vb;

	while (getline(inA, line)) 
	{
		vector<int> cur;
		cur.reserve(128);
		stringstream ss(line);

		ss >> line >> line >> line >> line;
		for (size_t i = 0; i < 128; ++i) 
		{
			ss >> thisOne;
			cur.push_back(thisOne);
		}
		va.push_back(cur);
	}

	while (getline(inB, line)) 
	{
		vector<int> cur;
		cur.reserve(128);
		stringstream ss(line);

		ss >> line >> line >> line >> line;
		for (size_t i = 0; i < 128; ++i) 
		{
			ss >> thisOne;
			cur.push_back(thisOne);
		}
		vb.push_back(cur);
	}

	size_t matchCnt = 0;
	for (size_t i = 0; i < va.size(); ++i) 
	{   
		size_t nearest = MAX_VECTOR_DIS;
		size_t secondNearest = MAX_VECTOR_DIS;
		for (size_t j = 0; j < vb.size(); ++j) 
		{   
			size_t cur = GetDis(va[i], vb[j]);
			if (cur < nearest) 
			{   
				nearest = cur;  
			}   
			else if (cur < secondNearest) 
			{   
				secondNearest = cur;
			}   
		}   
		if (nearest < secondNearest * MATCH_THRESHOLD) 
		{
			++matchCnt;
		}
	} 
	return 1.0 * matchCnt / va.size();
}

} /* end of visualrank */
} /* end of bingo */
