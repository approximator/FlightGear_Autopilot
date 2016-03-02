/*!
 * @file FgControlledAircraft.cpp
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "FgControlledAircraft.h"
#include "log.h"

#include <QSettings>
#include <assert.h>

FgControlledAircraft::FgControlledAircraft(QObject *parent)
    : FgAircraft(parent)
{
}

FgControlledAircraft::~FgControlledAircraft()
{
}

bool FgControlledAircraft::setConfig(QSettings &settings)
{
    bool result = false;
    settings.beginGroup("flightgear");
    do {
        set_callsign(settings.value("callsign").toString());
        if (callsign().isEmpty()) {
            qWarning() << "There is no callsign in the settings";
            break;
        }

        if (!m_Flightgear->setConfig(settings)) {
            qWarning() << "Cant set config for " << callsign() << " flightgear.";
            break;
        }

        connect(m_Flightgear->transport().get(), &FgTransport::fgDataReceived, this,
            &FgControlledAircraft::onFdmDataChanged);
        connect(&m_Flightgear->process(), static_cast<void (QProcess::*)(int)>(&QProcess::finished),
            [this](int) { emit flightgearFinished(); });
        connect(&m_Flightgear->process(), &QProcess::started, [this]() { emit flightgearStarted(); });
        connect(m_Flightgear.get(), &FgFlightgear::readyChanged,
            [this](bool ready) { emit flightgearReadyChanged(ready); });

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
    m_Autopilot->set_engaged(engage);
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
                                             /* .arg(rudder()) */
                                             .arg(rudder())
                                             .arg(throttle()));
}
