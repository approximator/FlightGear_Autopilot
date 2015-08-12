/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 12, 2015
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

    qreal lat = qDegreesToRadians(m_Latitude);
    qreal lon = qDegreesToRadians(m_Longitude);
    qreal r = 6371000 + m_Altitude;
    m_X = r * cos(lat) * cos(lon);
    m_Y = r * cos(lat) * sin(lon);
    m_Z = r * sin(lat);

//    qDebug() << callsign() << ": p = " << m_Pitch << ", r = " << m_Roll << ", y = " << m_Yaw
//             << ", lon = " << m_Longitude << ", lat = " << m_Latitude << ", alt = " << m_Altitude
//             << ", head = " << m_Heading;

    if (!connected())
    {
        m_Connected = true;
        emit onConnected();
    }

    emit paramsChanged();
}

