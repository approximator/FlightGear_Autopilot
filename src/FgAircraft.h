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

private:
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

#endif // FGAIRCRAFT_H
