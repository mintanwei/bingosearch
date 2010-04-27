/** 
 * @file common.h
 * @brief 
 * @author Chao Jiansong, jiansong.chaojs@gmail.com
 * @version 0.1
 * @date 2010-03-27
 */

#ifndef BINGO_COMMON_COMMON_H
#define BINGO_COMMON_COMMON_H

#include <string>
#include <algorithm>

using namespace std;

namespace bingo 
{
namespace common 
{

class Common 
{
public:
    Common();
    virtual ~Common();
    template<typename T> static const string itoa(const T value);

private:
};

template<typename T> const string Common::itoa(T value)
{
    string ret;
    string tmp;

    if (value == 0) 
    {
        return "0";
    }
    if (value < 0) 
    {
        ret.append(1, '-');
        value = -value;
    }
    while (value) 
    {
        tmp.append(1, value % 10 + '0');
        value /= 10;
    }
    reverse(tmp.begin(), tmp.end());
    ret.append(tmp);

    return ret;
}

} /* end of common */
} /* end of bingo */

#endif /* end of include guard: BINGO_COMMON_COMMON_H */
