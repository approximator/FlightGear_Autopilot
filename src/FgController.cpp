/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Feb 17, 2015
 */

#include "FgController.h"
#include "FgTransport.h"

FgController::FgController(QObject *parent) :
    QObject(parent),
    m_Transport(nullptr),
    m_OurAircrafts(),
    m_OtherAircrafts(),
    m_AircraftsCount(0)
{
    FgControlledAircraft* aircraft = new FgControlledAircraft("Not connected yet", this);
    m_Transport = aircraft->transport();
    m_OurAircrafts[aircraft->callsign()] = aircraft;

    //! @todo Connections!!
    connect(m_Transport, SIGNAL(fgDataReceived()), this, SLOT(onDataReceived()));
}

void FgController::updateAircraft(const QString & /* aircraftId */)
{
}

void FgController::onDataReceived()
{
    qDebug() << "On data received";
    //! @todo fix for several controlled aircrafts
    updateOurAircraftsCount();
    updateOtherAircraftsCount();

    emit fdmDataChanged(m_Transport);

    //eleron
    //elevator

    if (m_OurAircrafts.isEmpty())
    {
        return;
    }

    FgControlledAircraft* aircraft = *m_OurAircrafts.begin();
    QString data = QString::number(aircraft->ailerons()) + '\t' + QString::number(aircraft->elevator()) + "\n";
//    m_Transport->writeData(data);
}

void FgController::updateOurAircraftsCount()
{
    // currently we are dealing with one controlled aircraft
    //! @todo Add multiple aircrafts handling
    if (m_OurAircrafts.isEmpty())
    {
        return;
    }

    // add new aircraft to the list and emit signal
    QString callsign = m_Transport->getString("/sim/multiplay/callsign");
    if (callsign.isEmpty())
    {
        qDebug() << "ERROR! Our callsign is empty!";
    }

    FgControlledAircraft* aircraft = *m_OurAircrafts.begin();
    m_OurAircrafts.clear(); //! @fixme

    if (aircraft->callsign() == "Not connected yet")
    {
        aircraft->setCallsign(callsign);
        emit ourAircraftConnected(aircraft);

        connect(this, SIGNAL(fdmDataChanged(FgTransport*)), aircraft, SLOT(onFdmDataChanged(FgTransport*)));
        m_OurAircrafts[aircraft->callsign()] = aircraft; //! @fixme

        qDebug() << "ourAircraftConnected";
    }
}

void FgController::updateOtherAircraftsCount()
{
    qint32 count = m_Transport->getInt("/ai/models/num-players");

    if (m_AircraftsCount == count)
    {
        // assume that aircrafts remain the same
        return;
    }

    m_AircraftsCount = count;

    // get all aircrafts and add new ones to the list
    QList<QString> callsigns;
    for (int i = 0; i < count; ++i)
    {
        QString callsign = m_Transport->getString("/ai/models/multiplayer[" + QString::number(i) + "]/callsign");
        qDebug() << "callsign = " << callsign;
        callsigns.push_back(callsign);
        if (m_OtherAircrafts.contains(callsigns.back()))
        {
            continue;
        }

        FgAircraft* aircraft = new FgAircraft(callsign, this); //! @todo parent
        //! @todo  aircraft->setIndex();
        m_OtherAircrafts[callsign] = aircraft;
        emit aircraftConnected(aircraft);
        qDebug() << "otherAircraftConnected";
    }

    // remove disconnected aircrafts from the list
    auto it = m_OtherAircrafts.begin();
    while (it != m_OtherAircrafts.end())
    {
        if (!callsigns.contains((*it)->callsign()))
        {
            emit aircraftDisconnected(*it);
            qDebug() << "aircraftDisconnected";

            delete *it; //FIXME: check it with gui
            it = m_OtherAircrafts.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
