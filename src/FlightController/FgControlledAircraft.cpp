/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Jul 05, 2015
 */

#include "FgControlledAircraft.h"

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent)
{
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgControlledAircraft::onFdmDataChanged);
}

FgControlledAircraft::FgControlledAircraft(const QJsonObject &config, QObject *parent):
    FgAircraft("(none)", parent)
{
    setConfigFromJson(config);
    // TODO: fix
    connect(m_Transport.get(), &FgTransport::fgDataReceived, this, &FgControlledAircraft::onFdmDataChanged);
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
    m_Callsign = config["callsign"].toString(m_Callsign);

    QJsonObject flightgear = config["flightgear"].toObject();
    if (!flightgear.empty())
    {
        m_Flightgear = std::make_shared<FgFlightgear>(flightgear);
        m_Transport  = std::make_shared<FgTransport>(flightgear["port_in"].toInt(5556),
                                                     flightgear["port_out"].toInt(5555));
    }
    return true;
}

void FgControlledAircraft::runFlightGear()
{
    m_Flightgear->run();
}

void FgControlledAircraft::onFdmDataChanged()
{
    FgAircraft::onFdmDataChanged(*m_Transport.get());
    m_Autopilot->computeControl(this);
}


