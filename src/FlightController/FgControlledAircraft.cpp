/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Jul 16, 2015
 */

#include "FgControlledAircraft.h"

#include <fstream>

FgControlledAircraft::FgControlledAircraft(const QString &sign, QObject *parent) :
    FgAircraft(sign, parent)
{
    setConfigFromJson(QJsonObject());
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
    connect(&m_Flightgear->process(), static_cast<void (QProcess::*)(int)>(&QProcess::finished), [this](int){ emit flightgearFinished(); });
    connect(&m_Flightgear->process(), &QProcess::started , [this](){ emit flightgearStarted(); });
//    connect(this, &FgControlledAircraft::onConnected, [this](){ m_Autopilot->setDesiredHeading(heading()); });
    return true;
}

void FgControlledAircraft::runFlightGear(bool run)
{
    Q_UNUSED(run);
    m_Flightgear->run();
}

void FgControlledAircraft::onFdmDataChanged(const FgTransport &transport)
{
    FgAircraft::onFdmDataChanged(transport);

    if (!m_Autopilot->armed())
        return;

    m_Autopilot->computeControl(this);
    m_Flightgear->transport()->writeData(QString("%1\t%2\t%3\t%4\n")
                                         .arg(ailerons())
                                         .arg(elevator())
//                                         .arg(rudder())
                                         .arg(rudder())
                                         .arg(throttle()));

    std::ofstream f;
    f.open("/tmp/fgap.log", std::ios_base::app);
    f << m_Latitude << '\t' << m_Longitude << '\t' << m_Pitch << '\t' << m_Roll << '\t' <<
         m_Altitude << '\t' << m_Heading << '\t' << m_Ailerons << '\t' << m_Elevator << '\n';
}


