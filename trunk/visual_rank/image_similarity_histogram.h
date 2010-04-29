/** 
 * @file image_similarity_histogram.h
 * @brief 
 * @author Chao Jiansong, jiansong.chao@gmail.com
 * @version 0.1
 * @date 2010-04-28
 */

#ifndef BINGO_VISUAL_RANK_IMAGE_SIMILARITY_HISTOGRAM_H
#define BINGO_VISUAL_RANK_IMAGE_SIMILARITY_HISTOGRAM_H

#include "image_similarity.h"

namespace bingo 
{
namespace visualrank 
{

class ImageSimilarityHistogram : public ImageSimilarity 
{
public:
    ImageSimilarityHistogram();
    virtual ~ImageSimilarityHistogram();
    virtual double GetSimilarity(const std::string& imgFileA, const std::string& imgFileB) const;

private:
    /* data */
};

} // end of visualrank 
} // end of bingo 



#endif // end of include guard: BINGO_VISUAL_RANK_IMAGE_SIMILARITY_HISTOGRAM_H 
