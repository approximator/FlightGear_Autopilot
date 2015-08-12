/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Aug 12, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include <memory>
#include <QObject>
#include <QJsonObject>

class FgTransport;
class FgAutopilot;

class FgAircraft : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString callsign READ callsign NOTIFY callsignChanged)
    Q_PROPERTY(bool connected READ connected)
    Q_PROPERTY(QJsonObject params READ getParams NOTIFY paramsChanged)

public:
    explicit FgAircraft(const QString& sign, QObject *parent = 0);
    virtual ~FgAircraft();

    inline const QString callsign() const;
    inline qreal pitch() const;
    inline qreal roll() const;
    inline qreal yaw() const;
    inline qreal yawRate() const;
    inline qreal altitude() const;
    inline qreal verticalSpeed() const;
    inline qreal airspeed() const;
    inline qreal groundElev() const;
    inline qreal x() const;
    inline qreal y() const;
    inline qreal z() const;

    inline const QJsonObject getParams() const;
    inline qreal ailerons() const;
    inline qreal elevator() const;
    inline qreal   rudder() const;
    inline qreal throttle() const;
    inline qreal heading() const;
    inline bool connected() const;

    inline void setCallsign(const QString& newCallsign);
    inline void setConnected(bool _connected);

protected:
    QString m_Callsign   = "";
    qint32 m_Index       = -1;
    QJsonObject m_Params { };

    qreal m_Pitch     = 0.0; // deg
    qreal m_Roll      = 0.0; // deg
    qreal m_Yaw       = 0.0; // deg
    qreal m_YawRate   = 0.0; // degps
    qreal m_Longitude = 0.0; // deg
    qreal m_Latitude  = 0.0; // deg
    qreal m_Altitude  = 0.0; // ft
    qreal m_VerticalSpeed = 0.0;
    qreal m_Airspeed      = 0.0;
    qreal m_GroundLevel   = 0.0; // ft
    qreal m_Heading       = 0.0; // deg
    qreal m_X = 0.0;
    qreal m_Y = 0.0;
    qreal m_Z = 0.0;

    // controls
    qreal m_Ailerons = 0.0;
    qreal m_Elevator = 0.0;
    qreal m_Rudder   = 0.0;
    qreal m_Throttle = 0.9;
    bool m_Connected = false;

signals:
    void paramsChanged();
    void onConnected();
    void callsignChanged();

public slots:
    virtual void onFdmDataChanged(const FgTransport &transport);
};

//
const QString FgAircraft::callsign() const
{
    return m_Callsign;
}

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

qreal FgAircraft::altitude() const
{
    return m_Altitude;
}

qreal FgAircraft::verticalSpeed() const
{
    return m_VerticalSpeed;
}

qreal FgAircraft::airspeed() const
{
    return m_Airspeed;
}

qreal FgAircraft::groundElev() const
{
    return m_GroundLevel;
}

qreal FgAircraft::x() const
{
    return m_X;
}

qreal FgAircraft::y() const
{
    return m_Y;
}

qreal FgAircraft::z() const
{
    return m_Z;
}

const QJsonObject FgAircraft::getParams() const
{
    return m_Params;
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

bool FgAircraft::connected() const
{
    return m_Connected;
}

void FgAircraft::setCallsign(const QString &newCallsign)
{
    m_Callsign = newCallsign;
    emit callsignChanged();
}

void FgAircraft::setConnected(bool _connected)
{
    m_Connected = _connected;
}

Q_DECLARE_METATYPE(FgAircraft *)
#endif // FGAIRCRAFT_H
