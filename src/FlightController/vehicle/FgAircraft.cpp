/*!
 * @file FgAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Sep 03, 2015
 */

#include "FgMath.h"
#include "FgAircraft.h"
#include "flightgear/FgTransport.h"

FgAircraft::FgAircraft(QObject *parent) :
    FgVehicle(parent)
{
}

FgAircraft::~FgAircraft()
{
}

void FgAircraft::onFdmDataChanged(FgTransport* transport)
{
    FgVehicle::onFdmDataChanged(transport);
    m_Pitch     = transport->getFloat(PITCH);
    m_Roll      = transport->getFloat(ROLL);
    m_Yaw       = transport->getFloat(YAW);
    m_YawRate   = transport->getFloat(YAW_RATE);

    auto hdg        = transport->getFloat(HEADING);
    if (m_Heading != hdg)
    {
        m_Heading = hdg;
        emit headingChanged();
    }
    m_Airspeed  = transport->getFloat(AIRSPEED);
    m_VerticalSpeed = transport->getFloat(VERTICAL_SPEED);
}

