/*!
 * @file FgAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#ifndef FGAIRCRAFT_H
#define FGAIRCRAFT_H

#include <QObject>

class FgAircraft : public QObject
{
    Q_OBJECT
public:
    explicit FgAircraft(QObject *parent = 0);
    ~FgAircraft();

private:
    QString m_Callsign;

signals:

public slots:
};

#endif // FGAIRCRAFT_H
