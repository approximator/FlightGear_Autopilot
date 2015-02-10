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
#include "FgAircraft.h"

FgController::FgController(QObject *parent) :
    QObject(parent),
    m_Transport(0),
    m_OurAircrafts(),
    m_OtherAircrafts(),
    m_AircraftsCount(0)
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
    updateOurAircraftsCount();
    updateOtherAircraftsCount();
}

void FgController::updateOurAircraftsCount()
{
    // currently we are dealing with one controlled aircraft
    //! @todo Add multiple aircrafts handling
    if (!m_OurAircrafts.isEmpty())
    {
        return;
    }

    // add new aircraft to the list and emit signal
    QString callsign = m_Transport->getString("/sim/multiplay/callsign");
    if (callsign.isEmpty())
    {
        qDebug() << "ERROR! Our callsign is empty!";
    }

    FgAircraft* ourAircraft = new FgAircraft(callsign, this); //! @todo parent of ourAircraft
    m_OurAircrafts[ourAircraft->getCallsign()] = ourAircraft;
    emit ourAircraftConnected(ourAircraft);
    qDebug() << "ourAircraftConnected";
}

void FgController::updateOtherAircraftsCount()
{
    qint32 count = m_Transport->getInt("/ai/models/num-players");

    if (m_AircraftsCount == count)
    {
        // assume that aircrafts remain the same
        return;
    }

    //! @todo add or remove aircrafts
}
