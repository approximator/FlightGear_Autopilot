/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Feb 17, 2015
 */

#include "FgControlledAircraft.h"
#include "FgAutopilot.h"

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent),
    m_Transport(nullptr),
    m_Autopilot(nullptr)
{
    m_Transport = new FgTransport(this);
    m_Autopilot = new FgAutopilot(this);

    qDebug() << callsign() << " created.";
}

FgControlledAircraft::~FgControlledAircraft()
{
    qDebug() << callsign() << " destroyed.";
}

void FgControlledAircraft::onFdmDataChanged(FgTransport *transport)
{
    FgAircraft::onFdmDataChanged(transport);
    m_Autopilot->computeControl(this);
}


