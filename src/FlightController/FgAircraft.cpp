/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 05, 2015
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
        qDebug() << "Emit onConnected();";
        emit onConnected();
    }

    m_Pitch     = transport.getFloat("/orientation/pitch-deg");
    m_Roll      = transport.getFloat("/orientation/roll-deg");
    m_Yaw       = transport.getFloat("/orientation/yaw-deg");
    m_Longitude = transport.getFloat("/position/longitude-deg");
    m_Latitude  = transport.getFloat("/position/latitude-deg");
    m_Altitude  = transport.getFloat("/position/altitude-ft");
    m_Heading   = transport.getFloat("/orientation/heading-deg");

//    qDebug() << callsign() << ": p = " << m_Pitch << ", r = " << m_Roll << ", y = " << m_Yaw
//             << ", lon = " << m_Longitude << ", lat = " << m_Latitude << ", alt = " << m_Altitude
//             << ", head = " << m_Heading;

    emit paramsChanged();
}

