/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Jul 30, 2015
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

    switch (m_Mode)
    {
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

void FgAutopilot::holdVerticalSpeed(FgControlledAircraft *aircraft)
{
    qreal vsError = m_DesiredVerticalSpeed - aircraft->verticalSpeed();
    m_DesiredPitch = fgap::math::limit(m_VerticalSpeedPid.update(vsError), 20.0);
    holdAngles(aircraft);
}

void FgAutopilot::holdAltitude(FgControlledAircraft * aircraft)
{
    qreal altitudeError = m_DesiredAltitude - aircraft->altitude();
    m_DesiredVerticalSpeed = fgap::math::limit(altitudeError * 0.5, 25.0);
    holdVerticalSpeed(aircraft);
}

void FgAutopilot::holdAngles(FgControlledAircraft * aircraft)
{
    qreal pitch = aircraft->pitch();
    qreal roll = aircraft->roll();

    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = m_DesiredRoll - roll;

    // set controls
    aircraft->setElevator(fgap::math::limit(m_PitchPid.update(pitchError), 0.6));
    aircraft->setAilerons(fgap::math::limit(m_RollPid.update(rollError), 0.6));
}

void FgAutopilot::follow(FgControlledAircraft * aircraft, FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();
    m_DesiredRoll = followAircraft->roll();

    holdAltitude(aircraft);
}
