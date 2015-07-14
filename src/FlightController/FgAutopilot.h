/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Jul 14, 2015
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
        FG_MODE_ALTITUDE_HOLD,
        FG_MODE_ANGLES_HOLD,
        FG_MODE_FOLLOW
    } AUTOPILOT_MODE;

    explicit FgAutopilot(QObject *parent = 0);
    FgAutopilot(const FgAutopilot& other);
    FgAutopilot& operator=(const FgAutopilot& other);

    inline void engage(bool enable = true);
    inline void disarm();
    inline bool armed() const;

    inline void setFollow(FgAircraft *aircraft);
    inline void anglesHold(qreal roll = 0.0, qreal pitch = 3.0);
    inline void altitudeHold(qreal altitude = 2000);

    void computeControl(FgControlledAircraft *aircraft);

private:
    AUTOPILOT_MODE m_Mode = FG_MODE_ALTITUDE_HOLD;

    qreal m_DesiredPitch     = 0.0;    // deg
    qreal m_DesiredRoll      = 0.0;    // deg
    qreal m_DesiredYaw       = 0.0;    // deg
    qreal m_DesiredLongitude = 0.0;    // deg
    qreal m_DesiredLatitude  = 0.0;    // deg
    qreal m_DesiredAltitude  = 2000.0; // ft
    qreal m_DesiredHeading   = 0.0;    // deg

    FgPid m_PitchPid    { 0.04, 0.0, 0.005};
    FgPid m_RollPid     { 0.01, 0.1, 0.005};
    FgPid m_AltitudePid { 0.03, 0.01, 0.005};

    FgAircraft *m_toFollow { nullptr };

    bool m_Armed { false };

    void holdAltitude(FgControlledAircraft* aircraft);
    void holdAngles(FgControlledAircraft *aircraft);
    void follow(FgControlledAircraft* aircraft, FgAircraft *followAircraft);

signals:

public slots:

};

void FgAutopilot::engage(bool enable)
{
    m_Armed = enable;
}

void FgAutopilot::disarm()
{
    m_Armed = false;
}

bool FgAutopilot::armed() const
{
    return m_Armed;
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

#endif // FGAUTOPILOT_H
