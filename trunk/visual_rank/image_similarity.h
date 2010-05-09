/** 
 * @file image_similarity.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-06
 */

#ifndef BINGO_VISUAL_RANK_IMAGE_SIMILARITY_H
#define BINGO_VISUAL_RANK_IMAGE_SIMILARITY_H

#include <string>

namespace bingo 
{
namespace visualrank 
{

class ImageSimilarity 
{
public:
    ImageSimilarity();
    virtual ~ImageSimilarity();
    virtual double GetSimilarity(const std::string& imgFileA, const std::string& imgFileB);

protected:
    
};

} /* end of visualrank */
} /* end of bingo */



#endif /* end of include guard: BINGO_VISUAL_RANK_IMAGE_SIMILARITY_H */

