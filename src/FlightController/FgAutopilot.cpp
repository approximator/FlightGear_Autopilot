/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Aug 20, 2015
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
    qreal headingError = m_DesiredHeading - m_Aircraft->heading();
    qreal invertedHeadingError = 360 - std::fabs(headingError);


    qDebug() << "m_DesiredHeading = " << m_DesiredHeading;
    qDebug() << "       heading() = " << m_Aircraft->heading();
    qDebug() << "              he = " << headingError;
    qDebug() << "              ie = " << invertedHeadingError;

    if (invertedHeadingError < std::fabs(headingError))
        headingError = invertedHeadingError;

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

    qreal lat1 = m_Aircraft->latitude();
    qreal lon1 = m_Aircraft->longitude();
    qreal lat2 = followAircraft->latitude();
    qreal lon2 = followAircraft->longitude();

    // http://mathforum.org/library/drmath/view/55417.html
    qreal  y = std::sin(lon2-lon1) * std::cos(lat2);
    qreal  x = std::cos(lat1) * std::sin(lat2) -
               std::sin(lat1) * std::cos(lat2) * std::cos(lon2-lon1);
    if (y > 0)
    {
        if (x > 0)
            m_DesiredHeading = qRadiansToDegrees(std::atan(y / x));
        else if (x < 0)
            m_DesiredHeading = 180 - qRadiansToDegrees(std::atan(-y / x));
        else // (x == 0)
            m_DesiredHeading = 90;
    }
    else if (y < 0)
    {
        if (x > 0)
            m_DesiredHeading = 360 - qRadiansToDegrees(std::atan(-y / x));
        else if (x < 0)
            m_DesiredHeading = 180 + qRadiansToDegrees(std::atan(y / x));
        else
            m_DesiredHeading = 270;
    }
    else // (y == 0)
    {
        if (x > 0)
            m_DesiredHeading = 0;
        else if (x < 0)
            m_DesiredHeading = 180;
        // if (x == 0) then [the 2 points are the same]
    }

    holdHeading();
}
