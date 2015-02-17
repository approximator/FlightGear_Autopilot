/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 17, 2015
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
    virtual ~FgAircraft();

    inline const QString callsign() const;
    inline qreal pitch() const;
    inline qreal roll() const;
    inline qreal yaw() const;
    inline const QJsonObject getParams() const;

    inline void setCallsign(const QString& newCallsign);

protected:
    QString m_Callsign;
    qint32 m_Index;
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
    virtual void onFdmDataChanged(FgTransport* transport);
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

const QJsonObject FgAircraft::getParams() const
{
    return m_Params;
}

void FgAircraft::setCallsign(const QString &newCallsign)
{
    m_Callsign = newCallsign;
}

#endif // FGAIRCRAFT_H
