/*!
 * @file FgControlledAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified May 12, 2015
 */

#ifndef FGCONTROLLEDAIRCRAFT_H
#define FGCONTROLLEDAIRCRAFT_H

#include "FgAircraft.h"
#include "FgTransport.h"
#include "FgAutopilot.h"
#include "FgFlightgear.h"

#include <memory>

class FgControlledAircraft : public FgAircraft
{
    Q_OBJECT
public:
    explicit FgControlledAircraft(const QString& sign, QObject *parent = 0);
    ~FgControlledAircraft();

    inline std::shared_ptr<FgTransport> transport() const;

    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);

private:
    std::shared_ptr<FgTransport>  m_Transport  { std::make_shared<FgTransport>() };
    std::shared_ptr<FgAutopilot>  m_Autopilot  { std::make_shared<FgAutopilot>() };
    std::shared_ptr<FgFlightgear> m_Flightgear { std::make_shared<FgFlightgear>() };

signals:

public slots:
    virtual void onFdmDataChanged(std::shared_ptr<FgTransport> transport);
};

//
std::shared_ptr<FgTransport> FgControlledAircraft::transport() const
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
