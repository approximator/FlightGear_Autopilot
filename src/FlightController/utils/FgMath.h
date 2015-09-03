/*!
 * @file FgMath.h
 *
 * @brief Some useful math functions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 15, 2015
 * @date Modified Aug 21, 2015
 */

#ifndef FGMATH
#define FGMATH

#include <cmath>
#include <tuple>
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

inline double headingTo(double lat1, double lon1, double lat2, double lon2)
{
    double offset = 0;

    // http://mathforum.org/library/drmath/view/55417.html
    qreal  y = std::sin(lon2-lon1) * std::cos(lat2);
    qreal  x = std::cos(lat1) * std::sin(lat2) -
               std::sin(lat1) * std::cos(lat2) * std::cos(lon2-lon1);
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



//https://microem.ru/files/2012/08/GPS.G1-X-00006.pdf
//https://github.com/diydrones/ardupilot/blob/11625031990317bcf1cbf4903c0726ce6b264beb/libraries/AP_Math/AP_Math.h
// Semi-major axis of the Earth, in meters.
#define WGS84_A 6378137.0
//Inverse flattening of the Earth
#define WGS84_IF 298.257223563
// The flattening of the Earth
#define WGS84_F (1/WGS84_IF)
// Semi-minor axis of the Earth in meters
#define WGS84_B (WGS84_A*(1-WGS84_F))
// Eccentricity of the Earth
#define WGS84_E (sqrt(2*WGS84_F - WGS84_F*WGS84_F))

inline std::tuple<double, double, double> wgsToEcef(const double& lat, const double& lon, const double& h)
{
    const double d = WGS84_E * sin(lat);
    const double N = WGS84_A / sqrt(1. - d*d);

    double x = (N + h) * cos(lat) * cos(lon);
    double y = (N + h) * cos(lat) * sin(lon);
    double z = ((1 - WGS84_E*WGS84_E)*N + h) * sin(lat);

    return std::make_tuple(x, y, z);
}

} // namespace math
} // namespace fgap

#endif // FGMATH

