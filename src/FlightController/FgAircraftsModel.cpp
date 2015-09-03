/*!
 * @file FgAircraftsModel.cpp
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Sep 03, 2015
 */

#include "log.h"
#include "FgAircraftsModel.h"
#include "flightgear/FgTransport.h"

#include <QFile>
#include <QSettings>
#include <QCoreApplication>

FgAircraftsModel::FgAircraftsModel(QObject *parent) :
    QAbstractListModel(parent)
{
    init();
}

FgAircraftsModel::~FgAircraftsModel()
{
    saveConfig();
}

bool FgAircraftsModel::init()
{
    qDebug() << "Init FgAircraftsModel";

    QSettings settings;
    int size = settings.beginReadArray("aircrafts");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        if (!addAircraft(settings))
        {
            qWarning() << "Could not set settings for " << i << " aircraft. Skipping...";
            continue;
        }
    }
    settings.endArray();

//    m_OurAircrafts[0]->autopilot()->engage();
//    m_OurAircrafts[1]->autopilot()->engage();
//    m_OurAircrafts[1]->autopilot()->setFollow(m_OurAircrafts[0].get());
    return true;
}

bool FgAircraftsModel::saveConfig()
{
    QSettings settings;
    settings.beginWriteArray("aircrafts");
    for (int i = 0; i < m_OurAircrafts.size(); ++i)
    {
        settings.setArrayIndex(i);
        m_OurAircrafts.at(i)->saveConfig(settings);
    }
    settings.endArray();
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

bool FgAircraftsModel::addAircraft()
{
    QSettings settings;
    settings.beginGroup("basic_aircraft_config");
    return addAircraft(settings);
}

bool FgAircraftsModel::addAircraft(QSettings& settings)
{
    auto aircraft = std::make_shared<FgControlledAircraft>(this);
    if (!aircraft->setConfig(settings))
    {
        qWarning() << "Could not set settings for aircraft. Skipping...";
        return false;
    }

    if (aircraft->transport()->port() == 0 || aircraft->transport()->listenPort() == 0)
    {
        int port1 = 0;
        int port2 = 0;
        std::tie(port1, port2) = getAvailablePorts();
        aircraft->transport()->setPort(port1);
        aircraft->transport()->setListenPort(port2);
    }

    emit beginInsertRows(QModelIndex(), m_OurAircrafts.count(), m_OurAircrafts.count());
    m_OurAircrafts.append(aircraft);
    connect(aircraft.get(), &FgControlledAircraft::connectedChanged, this, &FgAircraftsModel::onAircraftConnected);
    emit endInsertRows();

    if (m_OurAircrafts.size() < 2)
    {
        m_Transport = m_OurAircrafts[0]->transport();
        connect(m_Transport, &FgTransport::fgDataReceived, this, &FgAircraftsModel::onDataReceived);
        qDebug() << "FgAircraftModel uses transport of " << m_OurAircrafts[0]->callsign();
    }

    return true;
}

QHash<int, QByteArray> FgAircraftsModel::roleNames() const
{
    return m_Roles;
}

std::tuple<int, int> FgAircraftsModel::getAvailablePorts() const
{
    auto a = std::max_element(
                std::begin(m_OurAircrafts), std::end(m_OurAircrafts),
                [](const std::shared_ptr<FgControlledAircraft>& a1,
                   const std::shared_ptr<FgControlledAircraft>& a2)
                {
                    return std::max(a1->transport()->listenPort(), a1->transport()->port()) <
                           std::max(a2->transport()->listenPort(), a2->transport()->port());
                });
    if (a == std::end(m_OurAircrafts))
        return std::make_tuple(8000, 8000 + 1);

    int port = std::max((*a)->transport()->listenPort(), (*a)->transport()->port()) + 1;
    return std::make_tuple(port, port + 1);
}

void FgAircraftsModel::onDataReceived(FgTransport *transport)
{
    emit fdmDataChanged(transport);

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
    if (!aircraft->connected())
        return; // TODO: set disconnect status if not connected

    emit dataChanged(QModelIndex(), index(m_OurAircrafts.size()-1), {Connected});
    qDebug() << "aircraft " << aircraft->callsign() << " connected";
}


