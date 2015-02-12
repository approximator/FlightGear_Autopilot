/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 12, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include <QObject>
#include <QJsonObject>

class FgAircraft : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString callsign READ callsign)
    Q_PROPERTY(QJsonObject params READ getParams NOTIFY paramsChanged)

public:
    explicit FgAircraft(const QString& sign, QObject *parent = 0);
    ~FgAircraft();

    inline QString callsign() const;
    const QJsonObject getParams() const { return m_params; }

private:
    QString m_Callsign;
    qint32 m_Index;
    QJsonObject m_params;

signals:
    void paramsChanged();

public slots:
};

inline QString FgAircraft::callsign() const
{
    return m_Callsign;
}

#endif // FGAIRCRAFT_H
