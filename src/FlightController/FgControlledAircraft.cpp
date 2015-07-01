/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Jul 01, 2015
 */

#include "FgControlledAircraft.h"

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent)
{
    qDebug() << "FgControlledAircraft::" << callsign() << " created.";
}

FgControlledAircraft::FgControlledAircraft(const QJsonObject &config, QObject *parent):
    FgAircraft("(none)", parent)
{
    setConfigFromJson(config);
    qDebug() << "FgControlledAircraft::" << callsign() << " created.";
}

FgControlledAircraft::~FgControlledAircraft()
{
    qDebug() << "FgControlledAircraft::" << callsign() << " destroyed.";
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
    m_Callsign = config["callsign"].toString(m_Callsign);

    m_Flightgear = std::make_shared<FgFlightgear>(config["flightgear"].toObject());
    return true;
}

void FgControlledAircraft::runFlightGear()
{
    m_Flightgear->run();
}

void FgControlledAircraft::onFdmDataChanged(std::shared_ptr<FgTransport> transport)
{
    FgAircraft::onFdmDataChanged(transport);
    m_Autopilot->computeControl(this);
}


