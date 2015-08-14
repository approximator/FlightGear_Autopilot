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

