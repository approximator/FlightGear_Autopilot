/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Dec 07, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include "FgVehicle.h"
#include "FgAircraft.h"
#include "flightgear/FgTransport.h"

class FgAircraft : public FgVehicle
{
    Q_OBJECT
    QML_READONLY_PROPERTY(qreal, heading)
    QML_READONLY_PROPERTY(qreal, pitch)
    QML_READONLY_PROPERTY(qreal, roll)
    QML_READONLY_PROPERTY(qreal, yaw)
    QML_READONLY_PROPERTY(qreal, yaw_rate)
    QML_READONLY_PROPERTY(qreal, vertical_speed)
    QML_READONLY_PROPERTY(qreal, airspeed)

    QML_WRITABLE_PROPERTY(qreal, ailerons)
    QML_WRITABLE_PROPERTY(qreal, elevator)
    QML_WRITABLE_PROPERTY(qreal, rudder)
    QML_WRITABLE_PROPERTY(qreal, throttle)

public:
    explicit FgAircraft(QObject *parent = 0):
        FgVehicle(parent),
        m_heading(0.0),
        m_pitch(0.0),
        m_roll(0.0),
        m_yaw(0.0),
        m_yaw_rate(0.0),
        m_vertical_speed(0.0),
        m_airspeed(0.0),
        m_ailerons(0.0),
        m_elevator(0.0),
        m_rudder(0.0),
        m_throttle(0.8)
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

#endif // FGAIRCRAFT_H
