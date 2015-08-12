/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Aug 12, 2015
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
    typedef enum
    {
        FG_MODE_YAW_RATE_HOLD,
        FG_MODE_HEADING_HOLD,
        FG_MODE_VERTICAL_SPEED_HOLD,
        FG_MODE_ALTITUDE_HOLD,
        FG_MODE_ANGLES_HOLD,
        FG_MODE_FOLLOW
    } AUTOPILOT_MODE;

    explicit FgAutopilot(QObject *parent = 0);
    FgAutopilot(const FgAutopilot& other);
    FgAutopilot& operator=(const FgAutopilot& other);

    Q_INVOKABLE inline void engage(bool enable = true);
    Q_INVOKABLE inline void disengage();
    Q_INVOKABLE bool engaged();

    inline void setFollow(FgAircraft *aircraft);
    inline void anglesHold(qreal roll = 0.0, qreal pitch = 3.0);
    inline void altitudeHold(qreal altitude = 2000);

    void computeControl(FgControlledAircraft *aircraft);

private:

    AUTOPILOT_MODE m_Mode = FG_MODE_HEADING_HOLD;
    bool m_Engaged { false };

    qreal m_DesiredPitch     = 0.0;    // deg
    qreal m_DesiredRoll      = 0.0;    // deg
    qreal m_DesiredYaw       = 0.0;    // deg
    qreal m_DesiredYawRate   = 0.0;    // deg
    qreal m_DesiredLongitude = 0.0;    // deg
    qreal m_DesiredLatitude  = 0.0;    // deg
    qreal m_DesiredAltitude  = 2000.0; // ft
    qreal m_DesiredHeading   = 50;     // deg
    qreal m_DesiredVerticalSpeed = -2.0;//

    FgPid m_PitchPid    { 0.015, 0.001, 0.005};
    FgPid m_RollPid     { 0.01, 0.001, 0.001};
    FgPid m_YawRatePid  { 0.5, 0.001, 0.0};
    FgPid m_VerticalSpeedPid { 0.05, 0.0, 0.01};

    FgAircraft *m_toFollow { nullptr };

    void holdYawRate(FgControlledAircraft* aircraft);
    void holdHeading(FgControlledAircraft* aircraft);
    void holdVerticalSpeed(FgControlledAircraft* aircraft);
    void holdAltitude(FgControlledAircraft* aircraft);
    void holdAngles(FgControlledAircraft *aircraft);
    void follow(FgControlledAircraft* aircraft, FgAircraft *followAircraft);

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
    m_Mode = FG_MODE_FOLLOW;
}

void FgAutopilot::anglesHold(qreal roll, qreal pitch)
{
    m_DesiredRoll = roll;
    m_DesiredPitch = pitch;
    m_Mode = FG_MODE_ANGLES_HOLD;
}

void FgAutopilot::altitudeHold(qreal altitude)
{
    m_DesiredAltitude = altitude;
    m_Mode = FG_MODE_ALTITUDE_HOLD;
}

Q_DECLARE_METATYPE(FgAutopilot *)

#endif // FGAUTOPILOT_H
