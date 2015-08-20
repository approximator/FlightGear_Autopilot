/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Aug 20, 2015
 */
#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include "FgPid.h"

#include <memory>
#include <QObject>

class FgControlledAircraft;
class FgAircraft;

class FgAutopilot : public QObject
{
    Q_OBJECT
public:
    explicit FgAutopilot(FgControlledAircraft* aircraft, QObject *parent = 0);
    FgAutopilot(const FgAutopilot& other);
    FgAutopilot& operator=(const FgAutopilot& other);

    Q_INVOKABLE inline void engage(bool enable = true);
    Q_INVOKABLE inline void disengage();
    Q_INVOKABLE bool engaged();

    inline void setFollow(FgAircraft *aircraft);
    inline void anglesHold(qreal roll = 0.0, qreal pitch = 3.0);
    inline void altitudeHold(qreal altitude = 2000);

    void computeControl();

private:
    FgControlledAircraft* m_Aircraft = nullptr;
    std::function<void()>  m_ControlFunc = [this](){ holdHeading(); };
    bool m_Engaged { false };

    qreal m_DesiredPitch     = 0.0;    // deg
    qreal m_DesiredRoll      = 0.0;    // deg
    qreal m_DesiredYaw       = 0.0;    // deg
    qreal m_DesiredYawRate   = 0.0;    // deg
    qreal m_DesiredLongitude = 0.0;    // deg
    qreal m_DesiredLatitude  = 0.0;    // deg
    qreal m_DesiredAltitude  = 2000.0; // ft
    qreal m_DesiredHeading   = 45;     // deg
    qreal m_DesiredVerticalSpeed = 1.0;//

    //                          kp         ki        kd    max_ouput  max_int
    FgPid m_PitchPid         { 0.02  ,   0.007 ,   0.001,  0.6    ,   10.0   };
    FgPid m_RollPid          { 0.01  ,   0.006 ,   0.001,  0.6    ,   10.0   };
    FgPid m_YawRatePid       { 0.8   ,   0.5   ,   0.002,  35.0   ,   22.0   };
    FgPid m_VerticalSpeedPid { 0.25  ,   0.045 ,   0.001,  20.0   ,   10.0   };

    FgAircraft *m_toFollow { nullptr };

    void holdYawRate();
    void holdHeading();
    void holdVerticalSpeed();
    void holdAltitude();
    void holdAngles();
    void follow(FgAircraft *followAircraft);

signals:

public slots:

};

void FgAutopilot::engage(bool enable)
{
    m_Engaged = enable;
}

void FgAutopilot::disengage()
{
    m_Engaged = false;
}

void FgAutopilot::setFollow(FgAircraft *aircraft)
{
    m_toFollow = aircraft;
    m_ControlFunc = [this](){ follow(m_toFollow); };
}

void FgAutopilot::anglesHold(qreal roll, qreal pitch)
{
    m_DesiredRoll = roll;
    m_DesiredPitch = pitch;
    m_ControlFunc = [this](){ holdAngles(); };
}

void FgAutopilot::altitudeHold(qreal altitude)
{
    m_DesiredAltitude = altitude;
    m_ControlFunc = [this](){ holdAltitude(); };
}

Q_DECLARE_METATYPE(FgAutopilot *)

#endif // FGAUTOPILOT_H
