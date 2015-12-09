/*!
 * @file FgAircraftsManager.cpp
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Dec 09, 2015
 */

#include "log.h"
#include "FgAircraftsManager.h"
#include "flightgear/FgTransport.h"

#include <QFile>
#include <QSettings>
#include <QCoreApplication>

FgAircraftsManager::FgAircraftsManager(QObject *parent) :
    QObject(parent),
    m_model(nullptr)
{
    init();
    qDebug() << "Air model";
}

FgAircraftsManager::~FgAircraftsManager()
{
    saveConfig();
}

bool FgAircraftsManager::init()
{
    qDebug() << "Init FgAircraftsManager";
    m_model = new TAirModel(this, "callsing", "aircraft");

    QSettings settings;
    qDebug() << "Reading settings from " << settings.fileName();
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

//    qobject_cast<FgAircraftAutopilot*>(m_OurAircrafts[0]->autopilot())->engage();
//    qobject_cast<FgAircraftAutopilot*>(m_OurAircrafts[1]->autopilot())->engage();
//    qobject_cast<FgAircraftAutopilot*>(m_OurAircrafts[1]->autopilot())->setFollow(m_OurAircrafts[0].get());
    return true;
}

bool FgAircraftsManager::saveConfig()
{
    QSettings settings;
    settings.beginWriteArray("aircrafts");
    int i = 0;
    for (auto aircraft = m_model->constBegin(); aircraft != m_model->constEnd(); ++aircraft)
    {
        settings.setArrayIndex(i++);
        (*aircraft)->saveConfig(settings);
    }
    settings.endArray();
    return true;
}


bool FgAircraftsManager::addAircraft()
{
    QSettings settings;
    settings.beginGroup("basic_aircraft_config"); // TODO: generate different callsigns
    return addAircraft(settings);
}

bool FgAircraftsManager::addAircraft(QSettings& settings)
{
    auto aircraft = new FgControlledAircraft(this);
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

    m_model->append(aircraft);
    if (m_model->size() < 2)
    {
        m_Transport = m_model->at(0)->transport();
        connect(m_Transport, &FgTransport::fgDataReceived, this, &FgAircraftsManager::onDataReceived);
        qDebug() << "FgAircraftModel uses transport of " << m_model->at(0)->callsign();
    }

    return true;
}

std::tuple<int, int> FgAircraftsManager::getAvailablePorts() const
{
    auto a = std::max_element(m_model->constBegin(), m_model->constEnd(),
                [](const FgControlledAircraft* a1,
                   const FgControlledAircraft* a2) {
                    return std::max(a1->transport()->listenPort(), a1->transport()->port()) <
                           std::max(a2->transport()->listenPort(), a2->transport()->port());
                });

    if (a == m_model->constEnd())
        return std::make_tuple(8000, 8000 + 1);

    auto transport = (*a)->transport();
    int port = std::max(transport->listenPort(), transport->port()) + 1;
    return std::make_tuple(port, port + 1);
}

void FgAircraftsManager::onDataReceived(FgTransport *transport)
{
    emit fdmDataChanged(transport);

    //eleron
    //elevator

    if (m_model->isEmpty())
    {
        qWarning() << "Model is empty!";
        return;
    }
}

void FgAircraftsManager::onAircraftConnected()
{
    FgAircraft *aircraft = static_cast<FgAircraft*>(sender());
    if (!aircraft->connected())
        return; // TODO: set disconnect status if not connected

    qDebug() << "aircraft " << aircraft->callsign() << " connected";
}


