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
    qreal altitude = aircraft->groundElev();
    qreal altitudeError = m_DesiredAltitude - altitude;

    m_DesiredPitch = fgap::math::limit(m_AltitudePid.update(altitudeError), 20.0);
//    m_DesiredRoll = m_HeadingPid.update(
//                fgap::math::limit(m_DesiredHeading - aircraft->heading(), 35.0)
//                );
//    qDebug() << "Heading " << m_DesiredHeading << "(" << aircraft->heading() << ")";
    holdAngles(aircraft);
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


//    qDebug() << "Pitch " << m_DesiredPitch << "(" << pitch << ")";
//    qDebug() << "Roll " << m_DesiredRoll << "(" << roll << ")";
//    qDebug() << "Elev " << m_DesiredAltitude << "(" << aircraft->groundElev() << ")";
}

void FgAutopilot::follow(FgControlledAircraft * aircraft, FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();
    m_DesiredRoll = followAircraft->roll();

    holdAltitude(aircraft);
}
