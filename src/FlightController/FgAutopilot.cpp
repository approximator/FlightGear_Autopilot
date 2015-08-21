/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Aug 21, 2015
 */

#include "log.h"
#include "FgAutopilot.h"
#include "FgControlledAircraft.h"

FgAutopilot::FgAutopilot(FgControlledAircraft *aircraft, QObject *parent) :
    QObject(parent)
{
    m_Aircraft = aircraft;
    qDebug() << "Autopilot created";
}

bool FgAutopilot::engaged()
{
    return m_Engaged;
}

void FgAutopilot::computeControl()
{
    if (!engaged())
        return;

    if (m_Aircraft->deltaTime() < 0.00001) // do not allow autopilot to go crazy with small doubles
    {
//        qWarning() << "Autopilot: Delta time is too small, giving up...";
        return;
    }

    if (m_Aircraft->elapsedTime() < 20) // just stabilize for the first 20 seconds of flight
    {
        holdAngles();
        return;
    }

    m_ControlFunc();
}

void FgAutopilot::holdYawRate()
{
    const qreal yawRateError = m_DesiredYawRate - m_Aircraft->yawRate();
    m_DesiredRoll = m_YawRatePid.update(yawRateError, m_Aircraft->deltaTime());
    holdAltitude();
}

void FgAutopilot::holdHeading()
{
    qreal headingError = fgap::math::headingOffset(m_Aircraft->heading(), m_DesiredHeading);

    qDebug() << "HE = " << headingError;

    m_DesiredYawRate = fgap::math::limit(headingError * 1, 5.0);
    holdYawRate();
}

void FgAutopilot::holdVerticalSpeed()
{
    const qreal vsError = m_DesiredVerticalSpeed - m_Aircraft->verticalSpeed();
    m_DesiredPitch = m_VerticalSpeedPid.update(vsError, m_Aircraft->deltaTime());

    holdAngles();

//    qDebug() << "    Yaw rate = " << m_Aircraft->yawRate() << "/" << m_DesiredYawRate;
//    qDebug() << "     Heading = " << m_Aircraft->heading() << "/" << m_DesiredHeading;
}

void FgAutopilot::holdAltitude()
{
    qreal altitudeError = m_DesiredAltitude - m_Aircraft->altitude();
    m_DesiredVerticalSpeed = fgap::math::limit(altitudeError * 0.8, 25.0);
    holdVerticalSpeed();
}

void FgAutopilot::holdAngles()
{
    qreal pitch = m_Aircraft->pitch();
    qreal roll = m_Aircraft->roll();

    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = m_DesiredRoll - roll;

    // set controls
    m_Aircraft->setElevator(m_PitchPid.update(pitchError, m_Aircraft->deltaTime()));
    m_Aircraft->setAilerons( m_RollPid.update(rollError , m_Aircraft->deltaTime()));

//    qDebug() << "Elapsed time = " << m_Aircraft->elapsedTime();
//    qDebug() << "  Delta time = " << m_Aircraft->deltaTime();
//    qDebug() << "          VS = " << m_Aircraft->verticalSpeed() << "/" << m_DesiredVerticalSpeed;
//    qDebug() << "       Pitch = " << m_Aircraft->pitch() << "/" << m_DesiredPitch;
//    qDebug() << "        Roll = " << m_Aircraft->roll() << "/" << m_DesiredRoll;
}

void FgAutopilot::follow(FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();

    m_DesiredHeading = fgap::math::headingTo(
                m_Aircraft->latitude(),
                m_Aircraft->longitude(),
                followAircraft->latitude(),
                followAircraft->longitude());

    holdHeading();
}
