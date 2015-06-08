/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified May 05, 2015
 */

#include "FgController.h"
#include "FgTransport.h"

FgController::FgController(QObject *parent) :
    QObject(parent)
{

}

bool FgController::init()
{
    auto aircraft = std::make_shared<FgControlledAircraft>("App1");
    m_Transport = aircraft->transport();
    m_OurAircrafts[aircraft->callsign()] = aircraft;

    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgController::onDataReceived);
    connect(this, &FgController::fdmDataChanged, aircraft.get(), &FgControlledAircraft::onFdmDataChanged);
    emit ourAircraftConnected(aircraft.get());

    return true;
}

void FgController::updateAircraft(const QString & /* aircraftId */)
{
}

void FgController::onDataReceived()
{
//    qDebug() << "On data received";
    //! @todo fix for several controlled aircrafts
    updateOurAircraftsCount();
    updateOtherAircraftsCount();

    emit fdmDataChanged(m_Transport);

    //eleron
    //elevator

    if (m_OurAircrafts.isEmpty())
    {
        qDebug() << "Our aircraft is empty!";
        return;
    }

    auto aircraft = *m_OurAircrafts.begin();
    QString data = QString::number(aircraft->ailerons()) + '\t' + QString::number(aircraft->elevator()) + "\n";
    m_Transport->writeData(data);
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

    if (!m_OurAircrafts.contains(callsign))
    {
        qDebug() << "WARNING! There is no " << callsign << " in the list";
        return;
    }

    auto aircraft = m_OurAircrafts[callsign];
    if (aircraft->connected())
    {
        return;
    }

    aircraft->setConnected(true);
    emit aircraftUpdated(aircraft.get());
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

        auto aircraft = std::make_shared<FgAircraft>(callsign);
        aircraft->setConnected(true);
        //! @todo  aircraft->setIndex();
        m_OtherAircrafts[callsign] = aircraft;
        emit aircraftConnected(aircraft.get());
        qDebug() << "otherAircraftConnected";
    }

    // remove disconnected aircrafts from the list
    auto it = m_OtherAircrafts.begin();
    while (it != m_OtherAircrafts.end())
    {
        if (!callsigns.contains((*it)->callsign()))
        {
            emit aircraftDisconnected((*it).get());
            qDebug() << "aircraftDisconnected";

            it = m_OtherAircrafts.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
