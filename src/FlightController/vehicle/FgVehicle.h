/*!
 * @file FgVehicle.h
 *
 * @brief Basic class of FlightGears vehicle
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 03, 2015
 * @date Modified Sep 03, 2015
 */

#ifndef FGVEHICLE_H
#define FGVEHICLE_H

#include <QObject>

class FgTransport;

class FgVehicle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString callsign READ callsign NOTIFY callsignChanged)
    Q_PROPERTY(bool connected READ connected NOTIFY connectedChanged)
    Q_PROPERTY(qreal lat READ latitude NOTIFY latChanged)
    Q_PROPERTY(qreal lon READ longitude NOTIFY lonChanged)
public:
    explicit FgVehicle(QObject *parent = 0);
    virtual ~FgVehicle();

    inline const QString callsign() const;
    inline qreal latitude() const;
    inline qreal longitude() const;
    inline qreal altitude() const;
    inline qreal groundElev() const;

    inline qreal deltaTime() const;
    inline qreal elapsedTime() const;
    inline bool connected() const;

    inline void setCallsign(const QString& newCallsign);
    inline void setConnected(bool _connected);

protected:
    QString m_Callsign    = "(no callsign)";
    qreal   m_Longitude   = 0.0; // deg
    qreal   m_Latitude    = 0.0; // deg
    qreal   m_Altitude    = 0.0; // ft
    qreal   m_GroundLevel = 0.0; // ft
    qreal   m_DeltaTime   = 0.0; // sec
    qreal   m_ElapsedTime = 0.0; // sec
    bool    m_Connected   = false;

signals:
    void connectedChanged();
    void callsignChanged();

    void latChanged();
    void lonChanged();

public slots:
    virtual void onFdmDataChanged(FgTransport *transport);
};

//
const QString FgVehicle::callsign() const
{
    return m_Callsign;
}

qreal FgVehicle::altitude() const
{
    return m_Altitude;
}

qreal FgVehicle::groundElev() const
{
    return m_GroundLevel;
}

qreal FgVehicle::latitude() const
{
    return m_Latitude;
}

qreal FgVehicle::longitude() const
{
    return m_Longitude;
}

qreal FgVehicle::deltaTime() const
{
    return m_DeltaTime;
}

qreal FgVehicle::elapsedTime() const
{
    return m_ElapsedTime;
}

bool FgVehicle::connected() const
{
    return m_Connected;
}

void FgVehicle::setCallsign(const QString &newCallsign)
{
    if (m_Callsign == newCallsign)
        return;

    m_Callsign = newCallsign;
    emit callsignChanged();
}

void FgVehicle::setConnected(bool _connected)
{
    if (m_Connected == _connected)
        return;
    m_Connected = _connected;
    emit connectedChanged();
}

#endif // FGVEHICLE_H
