/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 18, 2015
 */

#include "FgMath.h"
#include "FgAircraft.h"
#include "FgTransport.h"
#include "FgAutopilot.h"

FgAircraft::FgAircraft(const QString& sign, QObject *parent) :
    QObject(parent),
    m_Callsign(sign)
{
}

FgAircraft::~FgAircraft()
{
    qDebug() << callsign() << ": I am destroying";
}

void FgAircraft::onFdmDataChanged(const FgTransport& transport)
{
    m_Pitch     = transport.getFloat(PITCH);
    m_Roll      = transport.getFloat(ROLL);
    m_Yaw       = transport.getFloat(YAW);
    m_YawRate   = transport.getFloat(YAW_RATE);
    m_Heading   = transport.getFloat(HEADING);
    m_Longitude = transport.getFloat(LONGITUDE);
    m_Latitude  = transport.getFloat(LATITUDE);
    m_Altitude  = transport.getFloat(ALTITUDE);
    m_Airspeed  = transport.getFloat(AIRSPEED);
    m_GroundLevel   = transport.getFloat(ALTITUDE_AGL);
    m_VerticalSpeed = transport.getFloat(VERTICAL_SPEED);

    m_ElapsedTime = transport.getFloat(ELAPSED_TIME);
    m_DeltaTime = transport.getFloat(DELTA_TIME);

    const qreal lat = qDegreesToRadians(m_Latitude);
    const qreal lon = qDegreesToRadians(m_Longitude);

    std::tie(m_X, m_Y, m_Z) = fgap::math::wgsToEcef(lat, lon, m_Altitude);

//    qDebug() << callsign() << ": x = " << m_X << ", y = " << m_Y << ", z = " << m_Z
//             << ", lon = " << m_Longitude << ", lat = " << m_Latitude << ", alt = " << m_Altitude
//             << ", head = " << m_Heading;

    if (!connected())
    {
        m_Connected = true;
        emit onConnected();
    }

    emit paramsChanged();
}

