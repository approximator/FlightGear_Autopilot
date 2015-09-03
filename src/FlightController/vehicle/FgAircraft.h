/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Sep 03, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include "FgVehicle.h"

class FgAircraft : public FgVehicle
{
    Q_OBJECT
    Q_PROPERTY(qreal heading READ heading NOTIFY headingChanged)

public:
    explicit FgAircraft(QObject *parent = 0);
    virtual ~FgAircraft();

    inline qreal pitch() const;
    inline qreal roll() const;
    inline qreal yaw() const;
    inline qreal yawRate() const;
    inline qreal heading() const;
    inline qreal verticalSpeed() const;
    inline qreal airspeed() const;

    inline qreal ailerons() const;
    inline qreal elevator() const;
    inline qreal   rudder() const;
    inline qreal throttle() const;

protected:
    qint32 m_Index       = -1;

    qreal m_Pitch     = 0.0; // deg
    qreal m_Roll      = 0.0; // deg
    qreal m_Yaw       = 0.0; // deg
    qreal m_YawRate   = 0.0; // degps
    qreal m_VerticalSpeed = 0.0;
    qreal m_Airspeed      = 0.0;
    qreal m_Heading       = 0.0; // deg

    // controls
    qreal m_Ailerons = 0.0;
    qreal m_Elevator = 0.0;
    qreal m_Rudder   = 0.0;
    qreal m_Throttle = 0.9;

signals:
    void headingChanged();

public slots:
    virtual void onFdmDataChanged(FgTransport *transport);
};

//

qreal FgAircraft::pitch() const
{
    return m_Pitch;
}

qreal FgAircraft::roll() const
{
    return m_Roll;
}

qreal FgAircraft::yaw() const
{
    return m_Yaw;
}

qreal FgAircraft::yawRate() const
{
    return m_YawRate;
}

qreal FgAircraft::verticalSpeed() const
{
    return m_VerticalSpeed;
}

qreal FgAircraft::airspeed() const
{
    return m_Airspeed;
}

qreal FgAircraft::ailerons() const
{
    return m_Ailerons;
}

qreal FgAircraft::elevator() const
{
    return m_Elevator;
}

qreal FgAircraft::rudder() const
{
    return m_Rudder;
}

qreal FgAircraft::throttle() const
{
    return m_Throttle;
}

qreal FgAircraft::heading() const
{
    return m_Heading;
}

Q_DECLARE_METATYPE(FgAircraft *)
#endif // FGAIRCRAFT_H
