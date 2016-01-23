/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Sep 03, 2015
 * @date Modified Jan 24, 2016
 */
#ifndef FG_AIRCRAFT_AUTOPILOT_H
#define FG_AIRCRAFT_AUTOPILOT_H

#include "FgPid.h"
#include "FgAutopilot.h"

#include <functional>

#include <QObject>

class FgAircraft;
class FgControlledAircraft;

class FgAircraftAutopilot : public FgAutopilot
{
    Q_OBJECT
public:
    explicit FgAircraftAutopilot(FgControlledAircraft *aircraft, QObject *parent = 0);
    FgAircraftAutopilot(const FgAircraftAutopilot &other);
    FgAircraftAutopilot &operator=(const FgAircraftAutopilot &other);

    inline void setFollow(FgAircraft *aircraft);
    inline void anglesHold(qreal roll = 0.0, qreal pitch = 3.0);
    inline void altitudeHold(qreal altitude = 2000);

    virtual void computeControl();

private:
    std::function<void()> m_ControlFunc = [this]() { holdHeading(); };
    FgControlledAircraft *m_Aircraft = nullptr;

    qreal m_DesiredPitch         = 0.0;             // deg
    qreal m_DesiredRoll          = 0.0;             // deg
    qreal m_DesiredYaw           = 0.0;             // deg
    qreal m_DesiredYawRate       = 0.0;             // deg
    qreal m_DesiredLongitude     = 0.0;             // deg
    qreal m_DesiredLatitude      = 0.0;             // deg
    qreal m_DesiredAltitude      = 2000.0;          // ft
    qreal m_DesiredHeading       = 45;              // deg
    qreal m_DesiredVerticalSpeed = 1.0;             //

    /* clang-format off */
    /************************   kp         ki        kd    max_ouput  max_int */
    FgPid m_PitchPid         { 0.02  ,   0.007 ,   0.001,  0.6    ,   10.0   };
    FgPid m_RollPid          { 0.01  ,   0.006 ,   0.001,  0.6    ,   10.0   };
    FgPid m_YawRatePid       { 0.8   ,   0.5   ,   0.002,  35.0   ,   22.0   };
    FgPid m_VerticalSpeedPid { 0.25  ,   0.045 ,   0.001,  20.0   ,   10.0   };
    /* clang-format on */

    FgAircraft *m_toFollow{nullptr};

    void holdYawRate();
    void holdHeading();
    void holdVerticalSpeed();
    void holdAltitude();
    void holdAngles();
    void follow(FgAircraft *followAircraft);
};

void FgAircraftAutopilot::setFollow(FgAircraft *aircraft)
{
    m_toFollow    = aircraft;
    m_ControlFunc = [this]() { follow(m_toFollow); };
}

void FgAircraftAutopilot::anglesHold(qreal roll, qreal pitch)
{
    m_DesiredRoll  = roll;
    m_DesiredPitch = pitch;
    m_ControlFunc  = [this]() { holdAngles(); };
}

void FgAircraftAutopilot::altitudeHold(qreal altitude)
{
    m_DesiredAltitude = altitude;
    m_ControlFunc     = [this]() { holdAltitude(); };
}

Q_DECLARE_METATYPE(FgAircraftAutopilot *)

#endif /* FG_AIRCRAFT_AUTOPILOT_H */
