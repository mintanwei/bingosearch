/** 
 * @file visual_rank.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-04-06
 */

#ifndef BINGO_VISUAL_RANK_VISUAL_RANK_H
#define BINGO_VISUAL_RANK_VISUAL_RANK_H

#include "image_similarity.h"
#include "image_similarity_sift.h"
#include <vector>
#include <string>

namespace bingo 
{
namespace visualrank 
{

class VisualRank 
{
public:
    VisualRank();
    virtual ~VisualRank();
    void GetVisualRank(const std::string& path, ImageSimilarity* judge);
    void Output(const std::string& path);
private:
    size_t GetDirItemCount(const std::string& path);
    bool GaussTpivot(size_t n);

private:
    static const size_t IMAGE_PER_PATH = 1024;
    static const double DAMPING_FACTOR = 0.85;
    static const double EPS = 1e-8;

    double mRes[IMAGE_PER_PATH];
    double mMat[IMAGE_PER_PATH][IMAGE_PER_PATH];
    size_t mImageCount;
};


} /* end of visualrank */
} /* end of bingo */



#endif /* end of include guard: BINGO_VISUAL_RANK_VISUAL_RANK_H */

