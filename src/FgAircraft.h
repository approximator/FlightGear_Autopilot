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

    inline QString getString(const QString& node) const;
    inline qreal getFloat(const QString& node) const;
    inline qint32 getInt(const QString& node) const;

private:
    QString m_Callsign;

signals:

public slots:
};

#endif // FGAIRCRAFT_H
