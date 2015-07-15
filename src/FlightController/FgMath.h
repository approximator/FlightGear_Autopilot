/*!
 * @file FgMath.h
 *
 * @brief Some useful math functions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 15, 2015
 * @date Modified Jul 15, 2015
 */

#ifndef FGMATH
#define FGMATH

#include <cmath>

namespace fgap
{

namespace math
{



template <typename T>
T limit(const T& value, const T& _min_limit, const T& _max_limit)
{
    if (value < _min_limit)
        return _min_limit;

    if (value > _max_limit)
        return _max_limit;

    return value;
}

template <typename T>
T limit(const T& value, const T& _limit)
{
    return limit(value, -_limit, _limit);
}

} // namespace math
} // namespace fgap

#endif // FGMATH

