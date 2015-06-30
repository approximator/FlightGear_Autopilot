/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jun 30, 2015
 */

#include "FgController.h"
#include "FgTransport.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

FgController::FgController(QObject *parent) :
    QObject(parent)
{

}

FgController::~FgController()
{
//    saveConfig("./config/fgapConfig.json");
}

bool FgController::init()
{
    QFile configFile("./config/fgapConfig.json");
    if (!configFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open config file.");
        return false;
    }
    QJsonDocument configData(QJsonDocument::fromJson(configFile.readAll()));
    QJsonObject configObj = configData.object();
    QJsonArray aircrafts = configObj["aircrafts"].toArray();

    for (auto parameter : aircrafts)
    {
        auto aircraft = std::make_shared<FgControlledAircraft>(parameter.toObject());
        m_OurAircrafts.insert(aircraft->callsign(), aircraft);
        connect(this, &FgController::fdmDataChanged, aircraft.get(), &FgControlledAircraft::onFdmDataChanged);
        emit ourAircraftConnected(aircraft.get());
    }

    m_Transport = (*m_OurAircrafts.begin())->transport();
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgController::onDataReceived);

    return true;
}

void FgController::updateAircraft(const QString & /* aircraftId */)
{
}

void FgController::onDataReceived()
{
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
