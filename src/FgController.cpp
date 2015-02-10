/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Feb 10, 2015
 */

#include "FgController.h"
#include "FgTransport.h"

FgController::FgController(QObject *parent) :
    QObject(parent),
    m_Transport(0),
    m_OtherAircrafts()
{
    m_Transport = new FgTransport(this);
    //! @todo Connections!!
    connect(m_Transport, SIGNAL(fgDataReceived()), this, SLOT(onDataReceived()));
}

void FgController::updateAircraft(const QString & /* aircraftId */)
{
//    if (!m_OtherAircrafts.isEmpty())
//    {
//        FgAircraft *aircraft = m_OtherAircrafts.value(aircraftId);
//        emit aircraftUpdateded(aircraft);
//    }
}

void FgController::onDataReceived()
{
    qDebug() << "On data received";
    qDebug() << "Callsign = " << m_Transport->getString("/sim/multiplay/callsign");
//    if (!m_Aircrafts.contains(data))
//    {
//        FgAircraft *newAircraft = new FgAircraft(data);
//        m_Aircrafts[data] = newAircraft;
//        emit aircraftConnected(newAircraft);
//    }
//    else
//    {
//        emit aircraftUpdateded(m_Aircrafts.value(data));
//    }
}
