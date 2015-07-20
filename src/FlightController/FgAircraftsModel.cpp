/*!
 * @file FgAircraftsModel.cpp
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jul 20, 2015
 */

#include "FgAircraftsModel.h"
#include "FgTransport.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>

FgAircraftsModel::FgAircraftsModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

FgAircraftsModel::~FgAircraftsModel()
{
//    saveConfig("./config/fgapConfig.json");
}

bool FgAircraftsModel::init()
{
    QString configFileName("%1/%2/%3");
    configFileName = configFileName.arg(QCoreApplication::applicationDirPath(),
                                        CONFIG_PATH,
                                        "multiplayWithoutServer.json");
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
        m_OurAircrafts.append(aircraft);
        connect(aircraft.get(), &FgControlledAircraft::onConnected, this, &FgAircraftsModel::onAircraftConnected);
        emit ourAircraftAdded(aircraft.get());
    }

    m_Transport = m_OurAircrafts[0]->transport();
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgAircraftsModel::onDataReceived);

//    m_OurAircrafts["Travis"]->follow(m_OurAircrafts["Rover"].get());
//    m_OurAircrafts["Rover"]->autopilot()->engage();

//    m_OurAircrafts["Travis"]->runFlightGear();
//    m_OurAircrafts["Rover"]->runFlightGear();
    return true;
}

bool FgAircraftsModel::saveConfig(const QString &filename)
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

int FgAircraftsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    qDebug("Row count");
    return m_OurAircrafts.count();
}

QVariant FgAircraftsModel::data(const QModelIndex &index, int role) const
{
    qDebug("FgController::data. row = %d, role = %d", index.row(), role);
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_OurAircrafts.size())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_OurAircrafts[index.row()]->callsign();
    else
        return QVariant();
}

void FgAircraftsModel::updateAircraft(const QString & /* aircraftId */)
{
}

void FgAircraftsModel::onDataReceived()
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

void FgAircraftsModel::onAircraftConnected()
{
    FgAircraft *aircraft = static_cast<FgAircraft*>(sender());
    emit aircraftConnected(aircraft);
    qDebug() << "aircraft " << aircraft->callsign() << " connected";
}

void FgAircraftsModel::updateOtherAircraftsCount()
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
        if (m_OtherAircrafts.end() !=
                std::find_if(m_OtherAircrafts.begin(), m_OtherAircrafts.end(),
                             [&callsign](std::shared_ptr<FgAircraft> a){ return a->callsign() == callsign;}))
        {
            continue;
        }

        auto aircraft = std::make_shared<FgAircraft>(callsign);
        aircraft->setConnected(true);
        //! @todo  aircraft->setIndex();
        m_OtherAircrafts.append(aircraft);
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
