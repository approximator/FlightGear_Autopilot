/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified May 05, 2015
 */

#include "FgControlledAircraft.h"

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent)
{
    qDebug() << callsign() << " created.";
}

FgControlledAircraft::~FgControlledAircraft()
{
    qDebug() << callsign() << " destroyed.";
}

void FgControlledAircraft::onFdmDataChanged(std::shared_ptr<FgTransport> transport)
{
    FgAircraft::onFdmDataChanged(transport);
    m_Autopilot->computeControl(this);
}


