/*!
 * @file FgMath.h
 *
 * @brief Some useful math functions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 15, 2015
 * @date Modified Sep 09, 2015
 */

#ifndef FGMATH
#define FGMATH

#include <cmath>
#include <tuple>
#include <QtMath>
#include <QString>

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

inline double normalizeAngle_360(double angle)
{
    while (angle >= 360) angle -= 360;
    while (angle <  0)   angle += 360;
    return angle;
}

inline double normalizeAngle_180(double angle)
{
    while (angle >  180) angle -= 360;
    while (angle < -180) angle += 360;
    return angle;
}

inline double headingOffset(double heading1, double heading2)
{
    return normalizeAngle_180(heading2) - normalizeAngle_180(heading1);
}


template <typename T> inline T sqr(const T& x)
{
    return x * x;
}

inline double getDistance(double lat1, double lon1, double lat2, double lon2)
{
    using std::sin;
    using std::cos;
    using std::asin;
    using std::sqrt;
    lat1 = qDegreesToRadians(lat1);
    lon1 = qDegreesToRadians(lon1);
    lat2 = qDegreesToRadians(lat2);
    lon2 = qDegreesToRadians(lon2);

    double d = 2 * asin(sqrt(sqr(sin(lat1-lat2) / 2)) + cos(lat1) * cos(lat2) * sqr(sin((lon1-lon2)/2)));
    return d * 6366710; // TODO: define radius of Earth
}

inline double headingTo(double lat1, double lon1, double lat2, double lon2)
{
    using std::sin;
    using std::cos;
    using std::atan;
    double offset = 0;

    lat1 = qDegreesToRadians(lat1);
    lon1 = qDegreesToRadians(lon1);
    lat2 = qDegreesToRadians(lat2);
    lon2 = qDegreesToRadians(lon2);

    // http://mathforum.org/library/drmath/view/55417.html
    qreal  y = sin(lon2-lon1) * cos(lat2);
    qreal  x = cos(lat1) * sin(lat2) -
               sin(lat1) * cos(lat2) * cos(lon2-lon1);
    if (y > 0)
    {
        if (x > 0)
            offset = qRadiansToDegrees(std::atan(y / x));
        else if (x < 0)
            offset = 180 - qRadiansToDegrees(std::atan(-y / x));
        else // (x == 0)
            offset = 90;
    }
    else if (y < 0)
    {
        if (x > 0)
            offset = 360 - qRadiansToDegrees(std::atan(-y / x));
        else if (x < 0)
            offset = 180 + qRadiansToDegrees(std::atan(y / x));
        else
            offset = 270;
    }
    else // (y == 0)
    {
        if (x > 0)
            offset = 0;
        else if (x < 0)
            offset = 180;
        // if (x == 0) then [the 2 points are the same]
    }

    return offset;
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

inline std::tuple<int, int, int> degToMinSec(double deg)
{
    using std::fabs;
    int degrees = deg;
    double minutesD = fabs(deg - degrees) * 60.0;
    int minutes = minutesD;
    int seconds = (minutesD - minutes) * 60.0;
    return std::make_tuple(degrees, minutes, seconds);
}

inline QString degToMinSecStr(double deg)
{
    int degrees, minutes, seconds;
    std::tie(degrees, minutes, seconds) = degToMinSec(deg);
    return QString("%1°%2'%3\"").arg(degrees).arg(minutes).arg(seconds);
}

} // namespace math
} // namespace fgap

#endif // FGMATH

