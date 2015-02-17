/*!
 * @file FgControlledAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Feb 17, 2015
 */
#ifndef FGCONTROLLEDAIRCRAFT_H
#define FGCONTROLLEDAIRCRAFT_H

#include "FgAircraft.h"
#include "FgTransport.h"

class FgAutopilot;

class FgControlledAircraft : public FgAircraft
{
    Q_OBJECT
public:
    explicit FgControlledAircraft(const QString& sign, QObject *parent = 0);
    ~FgControlledAircraft();

    inline FgTransport* transport() const;

    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);

private:
    FgTransport* m_Transport;
    FgAutopilot* m_Autopilot;

signals:

public slots:
    virtual void onFdmDataChanged(FgTransport* transport);

};

//
FgTransport *FgControlledAircraft::transport() const
{
    return m_Transport;
}

void FgControlledAircraft::setAilerons(qreal val)
{
    m_Ailerons = val;
}

void FgControlledAircraft::setElevator(qreal val)
{
    m_Elevator = val;
}

void FgControlledAircraft::setRudder(qreal val)
{
    m_Rudder = val;
}

#endif // FGCONTROLLEDAIRCRAFT_H
