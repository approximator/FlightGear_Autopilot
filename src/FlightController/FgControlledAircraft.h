/*!
 * @file FgControlledAircraft.h
 *
 * @brief Aircraft abstraction of FlightGear's aircrafts that under our control
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 17, 2015
 * @date Modified Aug 01, 2015
 */

#ifndef FGCONTROLLEDAIRCRAFT_H
#define FGCONTROLLEDAIRCRAFT_H

#include "log.h"
#include "FgAircraft.h"
#include "FgTransport.h"
#include "FgAutopilot.h"
#include "FgFlightgear.h"

#include <memory>

class FgControlledAircraft : public FgAircraft
{
    Q_OBJECT
    Q_PROPERTY(bool autopilotEngaged READ autopilotEngaged)
    Q_PROPERTY(bool flightgearReady READ flightgearReady NOTIFY flightgearReadyChanged)
public:
    explicit FgControlledAircraft(const QJsonObject& config, QObject *parent = 0);
    ~FgControlledAircraft();

    inline std::shared_ptr<FgTransport> transport() const;
    inline bool autopilotEngaged() const;

    inline void setAilerons(qreal val);
    inline void setElevator(qreal val);
    inline void setRudder(qreal val);
    inline FgAutopilot *autopilot() const;
    inline bool flightgearReady() const;
    inline void follow(FgAircraft *aircraft);

    QJsonObject configurationAsJson() const;
    bool setConfigFromJson(const QJsonObject& config);

    Q_INVOKABLE void runFlightGear(bool run = true);
    Q_INVOKABLE void autopilotEngage(bool engage = true);
    inline const FgFlightgear& flightgear() const;

private:
    std::shared_ptr<FgAutopilot>  m_Autopilot  { std::make_shared<FgAutopilot>() };
    std::shared_ptr<FgFlightgear> m_Flightgear { };

signals:
    void flightgearStarted();
    void flightgearFinished();
    void flightgearReadyChanged(bool);

public slots:
    virtual void onFdmDataChanged(const FgTransport& transport);
};

//
std::shared_ptr<FgTransport> FgControlledAircraft::transport() const
{
    return m_Flightgear->transport();
}

bool FgControlledAircraft::autopilotEngaged() const
{
    return m_Autopilot->engaged();
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
    qDebug() << "Returning autopilot";
    return m_Autopilot.get();
}

bool FgControlledAircraft::flightgearReady() const
{
    qDebug() << "Return ready = " << m_Flightgear->ready();
    return m_Flightgear->ready();
}

void FgControlledAircraft::follow(FgAircraft *aircraft)
{
    m_Autopilot->setFollow(aircraft);
    m_Autopilot->engage();
}

const FgFlightgear &FgControlledAircraft::flightgear() const
{
    return *m_Flightgear.get();
}

Q_DECLARE_METATYPE(FgControlledAircraft *)

#endif // FGCONTROLLEDAIRCRAFT_H
