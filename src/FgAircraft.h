/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 13, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include <QObject>
#include <QJsonObject>

class FgTransport;
class FgAutopilot;

class FgAircraft : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString callsign READ callsign)
    Q_PROPERTY(QJsonObject params READ getParams NOTIFY paramsChanged)

public:
    explicit FgAircraft(const QString& sign, QObject *parent = 0);
    ~FgAircraft();

    inline const QString callsign() const;
    inline const QJsonObject getParams() const;
    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);

private:
    QString m_Callsign;
    qint32 m_Index;
    FgAutopilot* m_Autopilot;
    QJsonObject m_Params;

    qreal m_Pitch;      // deg
    qreal m_Roll;       // deg
    qreal m_Yaw;        // deg
    qreal m_Longitude;  // deg
    qreal m_Latitude;   // deg
    qreal m_Altitude;   // ft
    qreal m_Heading;    // deg

    // controls
    qreal m_Ailerons;
    qreal m_Elevator;
    qreal m_Rudder;

signals:
    void paramsChanged();

public slots:
    void onFdmDataChanged(FgTransport* transport);
};

//
const QString FgAircraft::callsign() const
{
    return m_Callsign;
}

const QJsonObject FgAircraft::getParams() const
{
    return m_Params;
}

void FgAircraft::setAilerons(qreal val)
{
    m_Ailerons = val;
}

void FgAircraft::setElevator(qreal val)
{
    m_Elevator = val;
}

void FgAircraft::setRudder(qreal val)
{
    m_Rudder = val;
}

#endif // FGAIRCRAFT_H
