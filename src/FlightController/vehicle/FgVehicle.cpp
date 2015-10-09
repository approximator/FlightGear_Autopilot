/*!
 * @file FgVehicle.cpp
 *
 * @brief Basic class of FlightGears vehicle
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 03, 2015
 * @date Modified Sep 03, 2015
 */

#include "FgVehicle.h"
#include "flightgear/FgTransport.h"

FgVehicle::FgVehicle(QObject *parent) : QObject(parent)
{

}

FgVehicle::~FgVehicle()
{
    qDebug() << callsign() << ": I am destroying";
}

void FgVehicle::onFdmDataChanged(FgTransport *transport)
{
    m_Longitude = transport->getFloat(LONGITUDE);
    m_Latitude  = transport->getFloat(LATITUDE);
    m_Altitude  = transport->getFloat(ALTITUDE);
    m_GroundLevel   = transport->getFloat(ALTITUDE_AGL);
    m_ElapsedTime = transport->getFloat(ELAPSED_TIME);
    m_DeltaTime = transport->getFloat(DELTA_TIME);

    if (!connected())
        setConnected(true);
}

