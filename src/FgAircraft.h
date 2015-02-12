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

class FgAircraft : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString callsign READ callsign)
public:
    explicit FgAircraft(const QString& sign, QObject *parent = 0);
    ~FgAircraft();

    inline QString callsign() const;

private:
    QString m_Callsign;
    qint32 m_Index;

signals:

public slots:
};

//

inline QString FgAircraft::callsign() const
{
    return m_Callsign;
}

#endif // FGAIRCRAFT_H
