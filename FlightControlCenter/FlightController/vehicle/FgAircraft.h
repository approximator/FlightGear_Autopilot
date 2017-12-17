/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
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

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include "FgAircraft.h"
#include "FgVehicle.h"
#include "flightgear/FgTransport.h"

class FgAircraft : public FgVehicle
{
    Q_OBJECT
    QML_READONLY_AUTO_PROPERTY(qreal, heading)
    QML_READONLY_AUTO_PROPERTY(qreal, pitch)
    QML_READONLY_AUTO_PROPERTY(qreal, roll)
    QML_READONLY_AUTO_PROPERTY(qreal, yaw)
    QML_READONLY_AUTO_PROPERTY(qreal, yaw_rate)
    QML_READONLY_AUTO_PROPERTY(qreal, vertical_speed)
    QML_READONLY_AUTO_PROPERTY(qreal, airspeed)

    QML_WRITABLE_AUTO_PROPERTY(qreal, ailerons)
    QML_WRITABLE_AUTO_PROPERTY(qreal, elevator)
    QML_WRITABLE_AUTO_PROPERTY(qreal, rudder)
    QML_WRITABLE_AUTO_PROPERTY(qreal, throttle)

public:
    explicit FgAircraft(QObject *parent = 0)
        : FgVehicle(parent)
        , m_heading(0.0)
        , m_pitch(0.0)
        , m_roll(0.0)
        , m_yaw(0.0)
        , m_yaw_rate(0.0)
        , m_vertical_speed(0.0)
        , m_airspeed(0.0)
        , m_ailerons(0.0)
        , m_elevator(0.0)
        , m_rudder(0.0)
        , m_throttle(0.8)
    {
    }

    virtual ~FgAircraft()
    {
    }

public slots:
    virtual void onFdmDataChanged(FgTransport *transport)
    {
        FgVehicle::onFdmDataChanged(transport);
        update_pitch(transport->getFloat(PITCH));
        update_roll(transport->getFloat(ROLL));
        update_yaw(transport->getFloat(YAW));
        update_yaw_rate(transport->getFloat(YAW_RATE));
        update_heading(transport->getFloat(HEADING));
        update_airspeed(transport->getFloat(AIRSPEED));
        update_vertical_speed(transport->getFloat(VERTICAL_SPEED));
    }
};

Q_DECLARE_METATYPE(FgAircraft *)

#endif /* FGAIRCRAFT_H */
