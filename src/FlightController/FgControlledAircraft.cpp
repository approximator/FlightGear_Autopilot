/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Jul 08, 2015
 */

#include "FgControlledAircraft.h"

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent)
{
    connect(m_Flightgear->transport().get(), &FgTransport::fgDataReceived, this, &FgControlledAircraft::onFdmDataChanged);
}

FgControlledAircraft::FgControlledAircraft(const QJsonObject &config, QObject *parent):
    FgAircraft("(none)", parent)
{
    setConfigFromJson(config);
}

FgControlledAircraft::~FgControlledAircraft()
{
}

QJsonObject FgControlledAircraft::configurationAsJson() const
{
    QJsonObject config;
    config["callsign"] = callsign();
    config["flightgear"] = m_Flightgear->configurationAsJson();

    return config;
}

bool FgControlledAircraft::setConfigFromJson(const QJsonObject &config)
{
    QJsonObject flightgear = config["flightgear"].toObject();
    if (!flightgear.empty())
    {
        m_Callsign = flightgear["callsign"].toString(m_Callsign);
        m_Flightgear = std::make_shared<FgFlightgear>(flightgear);
    }
    connect(m_Flightgear->transport().get(), &FgTransport::fgDataReceived, this, &FgControlledAircraft::onFdmDataChanged);
    return true;
}

void FgControlledAircraft::runFlightGear()
{
    m_Flightgear->run();
}

void FgControlledAircraft::onFdmDataChanged()
{
    FgAircraft::onFdmDataChanged(*m_Flightgear->transport().get());
    m_Autopilot->computeControl(this);
    m_Flightgear->transport()->writeData(QString("%1\t%2\n").arg(ailerons()).arg(elevator()));
//    qDebug() << callsign() << " : " << QString("%1\t%2\n").arg(ailerons()).arg(elevator());
}


