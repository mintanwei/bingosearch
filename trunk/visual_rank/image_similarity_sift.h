/** 
 * @file image_similarity_sift.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-05-09
 */

#ifndef BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H
#define BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H

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
	virtual double GetSimilarity(const std::string& fileA, const std::string& fileB) const;

private:
};

} /* end of visualrank */
} /* end of bingo */



#endif /* end of include guard: BINGO_VISUAL_RANK_IMAGE_SIMILARITY_SIFT_H */
