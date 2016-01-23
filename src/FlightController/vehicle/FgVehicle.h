/*!
 * @file FgVehicle.h
 *
 * @brief Basic class of FlightGears vehicle
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 03, 2015
 * @date Modified Jan 24, 2016
 */

#ifndef FGVEHICLE_H
#define FGVEHICLE_H

#include "QQmlVarPropertyHelpers.h"
#include "flightgear/FgTransport.h"

#include <QDebug>
#include <QObject>

class FgVehicle : public QObject
{
    Q_OBJECT
    QML_WRITABLE_VAR_PROPERTY(QString, callsign)
    QML_READONLY_VAR_PROPERTY(bool, connected)
    QML_READONLY_VAR_PROPERTY(qreal, latitude)
    QML_READONLY_VAR_PROPERTY(qreal, longitude)
    QML_READONLY_VAR_PROPERTY(qreal, altitude)
    QML_READONLY_VAR_PROPERTY(qreal, ground_level)
    QML_READONLY_VAR_PROPERTY(qreal, delta_time)
    QML_READONLY_VAR_PROPERTY(qreal, elapsed_time)

public:
    explicit FgVehicle(QObject *parent = 0)
        : QObject(parent)
        , m_callsign("(no callsign)")
        , m_connected(false)
        , m_latitude(0.0)
        , m_longitude(0.0)
        , m_altitude(0.0)
        , m_ground_level(0.0)
        , m_delta_time(0.0)
        , m_elapsed_time(0.0)
    {
    }

    virtual ~FgVehicle() { qDebug() << callsign() << ": I am destroying"; }

public slots:
    virtual void onFdmDataChanged(FgTransport *transport)
    {
        update_longitude(transport->getFloat(LONGITUDE));
        update_latitude(transport->getFloat(LATITUDE));
        update_altitude(transport->getFloat(ALTITUDE));
        update_ground_level(transport->getFloat(ALTITUDE_AGL));
        update_elapsed_time(transport->getFloat(ELAPSED_TIME));
        update_delta_time(transport->getFloat(DELTA_TIME));

        if (!connected())
            update_connected(true);
    }
};

#endif /* FGVEHICLE_H */
