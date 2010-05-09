/** 
 * @file image_similarity_sift.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-05-09
 */

#ifndef BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H
#define BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H

#include <set>
#include <string>
#include <vector>
#include "image_similarity.h"

namespace bingo 
{
namespace visualrank 
{

class ImageSimilaritySift : public ImageSimilarity
{
public:
	ImageSimilaritySift();
	virtual ~ImageSimilaritySift();
	virtual double GetSimilarity(const std::string& fileA, const std::string& fileB);

private:
	size_t GetDis(const std::vector<int>& va, const std::vector<int>& vb);

private:
	std::set<std::string> mFileSet;
	static const size_t MAX_VECTOR_DIS = 2000000000;
	static const double MATCH_THRESHOLD = 0.3;
};

} /* end of visualrank */
} /* end of bingo */



#endif /* end of include guard: BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H */
