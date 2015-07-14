/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Jul 14, 2015
 */

#include "FgAutopilot.h"
#include "FgControlledAircraft.h"

#include <QDebug>
#include <QVector3D>

FgAutopilot::FgAutopilot(QObject *parent) :
    QObject(parent)
{
}

void FgAutopilot::computeControl(FgControlledAircraft* aircraft)
{
    if (!armed())
        return;

    switch (m_Mode)
    {
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

void FgAutopilot::holdAltitude(FgControlledAircraft * aircraft)
{
    qreal altitude = aircraft->altitude();
    qreal altitudeError = m_DesiredAltitude - altitude;

    m_DesiredPitch = m_AltitudePid.update(altitudeError);
    holdAngles(aircraft);
}

void FgAutopilot::holdAngles(FgControlledAircraft * aircraft)
{
    qreal pitch = aircraft->pitch();
    qreal roll = aircraft->roll();

    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = m_DesiredRoll - roll;

    // set controls
    aircraft->setElevator(m_PitchPid.update(pitchError));
    aircraft->setAilerons(m_RollPid.update(rollError));

    qDebug() << "Pitch " << m_DesiredPitch << "(" << pitch << ")";
    qDebug() << "Roll " << m_DesiredRoll << "(" << roll << ")";
}

void FgAutopilot::follow(FgControlledAircraft * aircraft, FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();
    m_DesiredRoll = followAircraft->roll();

    holdAltitude(aircraft);
}
