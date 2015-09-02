/*!
 * @file FgControlledAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Sep 02, 2015
 */

#ifndef FGCONTROLLEDAIRCRAFT_H
#define FGCONTROLLEDAIRCRAFT_H

#include "log.h"
#include "FgAircraft.h"
#include "FgTransport.h"
#include "FgAutopilot.h"
#include "FgFlightgear.h"

#include <QSettings>

#include <memory>

class FgControlledAircraft : public FgAircraft
{
    Q_OBJECT
    Q_PROPERTY(bool autopilotEngaged READ autopilotEngaged)
    Q_PROPERTY(bool flightgearReady READ flightgearReady NOTIFY flightgearReadyChanged)
    Q_PROPERTY(FgTransport* transport READ transport NOTIFY transportChanged)
    Q_PROPERTY(FgFlightgear* flightgear READ flightgear NOTIFY flightgearChanged)
public:
    explicit FgControlledAircraft(QObject *parent = 0);
    ~FgControlledAircraft();

    inline FgAutopilot *autopilot() const;
    inline FgTransport *transport() const;
    inline FgFlightgear *flightgear() const;

    inline bool autopilotEngaged() const;
    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);
    inline bool flightgearReady() const;
    inline void follow(FgAircraft *aircraft);

    bool setConfig(QSettings &settings);
    bool saveConfig(QSettings &settings);

    Q_INVOKABLE void runFlightGear(bool run = true);
    Q_INVOKABLE void autopilotEngage(bool engage = true);

private:
    std::shared_ptr<FgAutopilot>  m_Autopilot  { std::make_shared<FgAutopilot>(this) };
    std::shared_ptr<FgFlightgear> m_Flightgear { std::make_shared<FgFlightgear>(this) };

signals:
    void flightgearStarted();
    void flightgearFinished();
    void flightgearReadyChanged(bool);
    void transportChanged();
    void flightgearChanged();

public slots:
    virtual void onFdmDataChanged(const FgTransport& transport);
};

//
bool FgControlledAircraft::autopilotEngaged() const
{
    return m_Autopilot ? m_Autopilot->engaged() : false;
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

FgAutopilot *FgControlledAircraft::autopilot() const
{
    return m_Autopilot.get();
}

FgTransport *FgControlledAircraft::transport() const
{
    return m_Flightgear->transport().get();
}

bool FgControlledAircraft::flightgearReady() const
{
    return m_Flightgear->ready();
}

void FgControlledAircraft::follow(FgAircraft *aircraft)
{
    m_Autopilot->setFollow(aircraft);
    m_Autopilot->engage();
}

FgFlightgear *FgControlledAircraft::flightgear() const
{
    return m_Flightgear.get();
}

Q_DECLARE_METATYPE(FgControlledAircraft *)

#endif // FGCONTROLLEDAIRCRAFT_H
