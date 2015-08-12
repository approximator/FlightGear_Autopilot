/*!
 * @file FgMath.h
 *
 * @brief Some useful math functions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 15, 2015
 * @date Modified Aug 12, 2015
 */

#ifndef FGMATH
#define FGMATH

#include <cmath>
#include <QtMath>

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

inline qreal rungeKutta(const qreal h, const qreal val)
{
    const qreal k1 = h * val;
    const qreal k2 = h * val + k1 / 2;
    const qreal k3 = h * val + k2 / 2;
    const qreal k4 = h * val + k3;
    const qreal d = (k1 + 2 * k2 + 2 * k3 + k4) / 6;
    return d;
}

} // namespace math
} // namespace fgap

#endif // FGMATH

