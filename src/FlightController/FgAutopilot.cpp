/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Aug 12, 2015
 */

#include "log.h"
#include "FgAutopilot.h"
#include "FgControlledAircraft.h"

#include <QVector3D>

FgAutopilot::FgAutopilot(QObject *parent) :
    QObject(parent)
{
    qDebug() << "Autopilot created";
}

bool FgAutopilot::engaged()
{
    return m_Engaged;
}

void FgAutopilot::computeControl(FgControlledAircraft* aircraft)
{
    if (!engaged())
        return;

    if (aircraft->deltaTime() < 0.00001) // do not allow autopilot to go crazy with small doubles
    {
//        qWarning() << "Autopilot: Delta time is too small, giving up...";
        return;
    }

    if (aircraft->elapsedTime() < 20) // just stabilize for the first 20 seconds of flight
    {
        holdAngles(aircraft);
        return;
    }

    switch (m_Mode)
    {
    case FG_MODE_YAW_RATE_HOLD:
        holdYawRate(aircraft);
        break;
    case FG_MODE_HEADING_HOLD:
        holdHeading(aircraft);
        break;
    case FG_MODE_VERTICAL_SPEED_HOLD:
        holdVerticalSpeed(aircraft);
        break;
    case FG_MODE_ALTITUDE_HOLD:
        holdAltitude(aircraft);
        break;
    case FG_MODE_ANGLES_HOLD:
        holdAngles(aircraft);
        break;
    case FG_MODE_FOLLOW:
        follow(aircraft, m_toFollow);
        break;
    default:
        break;
    }
}

void FgAutopilot::holdYawRate(FgControlledAircraft *aircraft)
{
    const qreal yawRateError = m_DesiredYawRate - aircraft->yawRate();
    m_DesiredRoll = fgap::math::limit(m_YawRatePid.update(yawRateError, aircraft->deltaTime()), 35.0);
    holdAltitude(aircraft);
}

void FgAutopilot::holdHeading(FgControlledAircraft *aircraft)
{
    m_DesiredYawRate = fgap::math::limit(m_DesiredHeading-aircraft->heading() * 1, 5.0);
    holdYawRate(aircraft);
}

void FgAutopilot::holdVerticalSpeed(FgControlledAircraft *aircraft)
{
    const qreal vsError = m_DesiredVerticalSpeed - aircraft->verticalSpeed();
    m_DesiredPitch = fgap::math::limit(m_VerticalSpeedPid.update(vsError, aircraft->deltaTime()), 20.0);

    holdAngles(aircraft);

//    qDebug() << "    Yaw rate = " << aircraft->yawRate() << "/" << m_DesiredYawRate;
//    qDebug() << "     Heading = " << aircraft->heading() << "/" << m_DesiredHeading;
}

void FgAutopilot::holdAltitude(FgControlledAircraft * aircraft)
{
    qreal altitudeError = m_DesiredAltitude - aircraft->altitude();
    m_DesiredVerticalSpeed = fgap::math::limit(altitudeError * 0.8, 25.0);
    holdVerticalSpeed(aircraft);
}

void FgAutopilot::holdAngles(FgControlledAircraft * aircraft)
{
    qreal pitch = aircraft->pitch();
    qreal roll = aircraft->roll();

    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = m_DesiredRoll - roll;

    // set controls
    aircraft->setElevator(fgap::math::limit(m_PitchPid.update(pitchError, aircraft->deltaTime()), 0.6));
    aircraft->setAilerons(fgap::math::limit(m_RollPid.update(rollError, aircraft->deltaTime()), 0.6));

//    qDebug() << "Elapsed time = " << aircraft->elapsedTime();
//    qDebug() << "  Delta time = " << aircraft->deltaTime();
//    qDebug() << "          VS = " << aircraft->verticalSpeed() << "/" << m_DesiredVerticalSpeed;
//    qDebug() << "       Pitch = " << aircraft->pitch() << "/" << m_DesiredPitch;
//    qDebug() << "        Roll = " << aircraft->roll() << "/" << m_DesiredRoll;
}

void FgAutopilot::follow(FgControlledAircraft * aircraft, FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();
    m_DesiredRoll = followAircraft->roll();

    holdAltitude(aircraft);
}
