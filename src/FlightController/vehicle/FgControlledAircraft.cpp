/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Sep 03, 2015
 */

#include "log.h"
#include "FgControlledAircraft.h"

#include <assert.h>
#include <QSettings>

FgControlledAircraft::FgControlledAircraft(QObject *parent):
    FgAircraft(parent)
{

}

FgControlledAircraft::~FgControlledAircraft()
{
}

bool FgControlledAircraft::setConfig(QSettings &settings)
{
    bool result = false;
    settings.beginGroup("flightgear");
    do
    {
        m_Callsign = settings.value("callsign").toString();
        if (m_Callsign.isEmpty())
        {
            qWarning() << "There is no callsign in the settings";
            break;
        }

        if (!m_Flightgear->setConfig(settings))
        {
            qWarning() << "Cant set config for " << callsign() << " flightgear.";
            break;
        }

        connect(m_Flightgear->transport().get(), &FgTransport::fgDataReceived, this, &FgControlledAircraft::onFdmDataChanged);
        connect(&m_Flightgear->process(), static_cast<void (QProcess::*)(int)>(&QProcess::finished), [this](int){ emit flightgearFinished(); });
        connect(&m_Flightgear->process(), &QProcess::started , [this](){ emit flightgearStarted(); });
        connect(m_Flightgear.get(), &FgFlightgear::readyChanged,
                [this](bool ready){ emit flightgearReadyChanged(ready); });

        result = true;
    } while (0);

    settings.endGroup();
    return result;
}

bool FgControlledAircraft::saveConfig(QSettings &settings)
{
    settings.beginGroup("flightgear");
    m_Flightgear->saveConfig(settings);
    settings.endGroup();
    return true;
}

void FgControlledAircraft::runFlightGear(bool run)
{
    Q_UNUSED(run);
    m_Flightgear->run();
}

void FgControlledAircraft::autopilotEngage(bool engage)
{
    assert(m_Autopilot);
    m_Autopilot->engage(engage);
}

void FgControlledAircraft::onFdmDataChanged(FgTransport *transport)
{
    assert(m_Autopilot);
    FgAircraft::onFdmDataChanged(transport);

    if (!m_Autopilot->engaged())
        return;

    m_Autopilot->computeControl();
    m_Flightgear->transport()->writeData(QString("%1\t%2\t%3\t%4\n")
                                         .arg(ailerons())
                                         .arg(elevator())
//                                         .arg(rudder())
                                         .arg(rudder())
                                         .arg(throttle()));
}


