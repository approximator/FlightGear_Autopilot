/*!
 * @file FgAircraftsModel.cpp
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Aug 21, 2015
 */

#include "log.h"
#include "FgTransport.h"
#include "FgAircraftsModel.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QCoreApplication>

FgAircraftsModel::FgAircraftsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    init();
}

FgAircraftsModel::~FgAircraftsModel()
{
//    saveConfig("./config/fgapConfig.json");
}

bool FgAircraftsModel::init()
{
    qDebug() << "Init FgAircraftsModel";
    QString configFileName("%1/%2/%3");
    configFileName = configFileName.arg(QCoreApplication::applicationDirPath(),
                                        CONFIG_PATH,
                                        "multiplayWithoutServer.json");

    qDebug() << "Reading config " << configFileName;
    QFile configFile(configFileName);
    if (!configFile.open(QIODevice::ReadOnly))
    {
        qWarning() << "Couldn't open config file: " <<  configFileName;
        return false;
    }
    QJsonDocument configData(QJsonDocument::fromJson(configFile.readAll()));
    QJsonObject configObj = configData.object();
    QJsonArray aircrafts = configObj["aircrafts"].toArray();

    for (auto const &parameter : aircrafts)
    {
        auto aircraft = std::make_shared<FgControlledAircraft>(parameter.toObject(), this);
        emit beginInsertRows(QModelIndex(), m_OurAircrafts.count(), m_OurAircrafts.count());
        m_OurAircrafts.append(aircraft);
        connect(aircraft.get(), &FgControlledAircraft::onConnected, this, &FgAircraftsModel::onAircraftConnected);
        emit endInsertRows();
    }

    m_Transport = m_OurAircrafts[0]->transport();
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgAircraftsModel::onDataReceived);

//    m_OurAircrafts[0]->runFlightGear();
//    m_OurAircrafts[0]->autopilot()->engage();
//    m_OurAircrafts[1]->autopilot()->engage();
//    m_OurAircrafts[1]->autopilot()->setFollow(m_OurAircrafts[0].get());
    return true;
}

bool FgAircraftsModel::saveConfig(const QString &filename)
{
    QFile saveFile(filename);

    if (!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning() << "Couldn't open save file.";
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
    return m_OurAircrafts.count();
}

QVariant FgAircraftsModel::data(const QModelIndex &index, int role) const
{
//    LOG("FgAircraftsModel::data. row = %d, role = %s", index.row(), m_Roles[role].c_str());
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() >= m_OurAircrafts.size())
        return QVariant();

    switch (role)
    {
    case Name:
    case Qt::DisplayRole:
        return QVariant::fromValue(m_OurAircrafts[index.row()]->callsign());
        break;
    case Connected:
        return QVariant::fromValue(m_OurAircrafts[index.row()]->connected());
        break;
     case Aircraft:
        return QVariant::fromValue(m_OurAircrafts[index.row()].get());
    default:
        return QVariant();
        break;
    }

    return QVariant();
}

FgControlledAircraft* FgAircraftsModel::get(int index) const
{
    if (index < 0 || index > m_OurAircrafts.length())
    {
        qWarning() << "Requested invalid index: " << index;
        return 0;
    }
    return m_OurAircrafts.at(index).get();
}

void FgAircraftsModel::runFlightgear(int index) const
{
    m_OurAircrafts[index]->runFlightGear();
}

QHash<int, QByteArray> FgAircraftsModel::roleNames() const
{
    return m_Roles;
}

void FgAircraftsModel::updateAircraft(const QString & /* aircraftId */)
{
}

void FgAircraftsModel::onDataReceived()
{
    emit fdmDataChanged(m_Transport);

    //eleron
    //elevator

    if (m_OurAircrafts.isEmpty())
    {
        qWarning() << "Our aircraft is empty!";
        return;
    }
}

void FgAircraftsModel::onAircraftConnected()
{
    FgAircraft *aircraft = static_cast<FgAircraft*>(sender());

    emit dataChanged(QModelIndex(), index(m_OurAircrafts.size()-1), {Connected});
    qDebug() << "aircraft " << aircraft->callsign() << " connected";
}


