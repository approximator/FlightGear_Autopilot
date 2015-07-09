/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jul 09, 2015
 */

#include "FgController.h"
#include "FgTransport.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>

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
    // FIX: filename determining
    QString configFileName = QCoreApplication::applicationDirPath() + "/config/multiplayWithoutServer.json";
    QFile configFile(configFileName);
    if (!configFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open config file: %s",  configFileName.toStdString().c_str());
        return false;
    }
    QJsonDocument configData(QJsonDocument::fromJson(configFile.readAll()));
    QJsonObject configObj = configData.object();
    QJsonArray aircrafts = configObj["aircrafts"].toArray();

    for (auto const &parameter : aircrafts)
    {
        auto aircraft = std::make_shared<FgControlledAircraft>(parameter.toObject());
        m_OurAircrafts.insert(aircraft->callsign(), aircraft);
        connect(aircraft.get(), &FgControlledAircraft::onConnected, this, &FgController::onAircraftConnected);
        emit ourAircraftAdded(aircraft.get());
    }

    m_Transport = m_OurAircrafts["Travis"]->transport();
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgController::onDataReceived);

//    m_OurAircrafts["Travis"]->follow(m_OurAircrafts["Rover"].get());
////    m_OurAircrafts["Travis"]->autopilot()->arm();

//    m_OurAircrafts["Travis"]->runFlightGear();
//    m_OurAircrafts["Rover"]->runFlightGear();
    return true;
}

bool FgController::saveConfig(const QString &filename)
{
    QFile saveFile(filename);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonArray aircrafts;
    for (auto &aircraft : m_OurAircrafts)
        aircrafts.append(aircraft->configurationAsJson());

    QJsonObject config;
    config["aircrafts"] = aircrafts;
    QJsonDocument saveDoc(config);
    saveFile.write(saveDoc.toJson());

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
}

void FgController::onAircraftConnected()
{
    FgAircraft *aircraft = static_cast<FgAircraft*>(sender());
    emit aircraftConnected(aircraft);
    qDebug() << "aircraft " << aircraft->callsign() << " connected";
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
        emit aircraftAdded(aircraft.get());
        qDebug() << "otherAircraftAdded";
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
