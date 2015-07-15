/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 07, 2015
 */

#include "FgAircraft.h"
#include "FgTransport.h"
#include "FgAutopilot.h"

#include <QDebug>

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
    if (!connected())
    {
        m_Connected = true;
        emit onConnected();
    }

    m_Pitch     = transport.getFloat("/orientation/pitch-deg");
    m_Roll      = transport.getFloat("/orientation/roll-deg");
    m_Yaw       = transport.getFloat("/orientation/yaw-deg");
    m_Longitude = transport.getFloat("/position/longitude-deg");
    m_Latitude  = transport.getFloat("/position/latitude-deg");
    m_Altitude  = transport.getFloat("/position/altitude-ft");
    m_GroundLevel = transport.getFloat("/position/altitude-agl-ft");
    m_Heading   = transport.getFloat("/orientation/heading-deg");

    qreal lat = qDegreesToRadians(m_Latitude);
    qreal lon = qDegreesToRadians(m_Longitude);
    qreal r = 6371000 + m_Altitude;
    m_X = r * cos(lat) * cos(lon);
    m_Y = r * cos(lat) * sin(lon);
    m_Z = r * sin(lat);

//    qDebug() << callsign() << ": p = " << m_Pitch << ", r = " << m_Roll << ", y = " << m_Yaw
//             << ", lon = " << m_Longitude << ", lat = " << m_Latitude << ", alt = " << m_Altitude
//             << ", head = " << m_Heading;

    emit paramsChanged();
}

