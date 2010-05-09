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

double ImageSimilaritySift::GetSimilarity(const string& fileA, const string& fileB) const
{
	ifstream in1(fileA.c_str());
	if (in1.fail()) 
	{
		Log::Output((string)("FAIL TO OPEN ") + fileA, Log::ERROR);
		exit(1);
	}
	ifstream in2(fileB.c_str());
	if (in2.fail()) 
	{
		Log::Output((string)("FAIL TO OPEN ") + fileB, Log::ERROR);
		exit(1);
	}

	system(((string)("convert ") + fileA + " a.pgm").c_str());
	system(((string)("convert ") + fileB + " b.pgm").c_str());
	system("../third_party/siftpp/sift a.pgm");
	system("../third_party/siftpp/sift b.pgm");
}

} /* end of visualrank */
} /* end of bingo */
