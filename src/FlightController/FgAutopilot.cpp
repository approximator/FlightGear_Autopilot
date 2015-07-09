/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified May 05, 2015
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
    qreal altitudeError = altitude - m_DesiredAltitude;
    qreal pitchOut = altitudeError * -0.2;
//    if (pitchOut > 0)


    // limit control outputs
    if (qAbs(pitchOut) > 30)
        pitchOut = (pitchOut / qAbs(pitchOut)) * 30;
    m_DesiredPitch = pitchOut;

//    qDebug() << "Altitude " << m_DesiredAltitude << "(" << altitude << ")";

    holdAngles(aircraft);
}

void FgAutopilot::holdAngles(FgControlledAircraft * aircraft)
{
    qreal pitch = aircraft->pitch();
    qreal roll = aircraft->roll();

    // simple proportional control
    //! @todo improve this
    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = roll - m_DesiredRoll;

    qreal pitchOut = pitchError * 0.03;
    qreal rollOut = rollError * -0.02;

    // limit control outputs
    if (qAbs(pitchOut) > 0.6)
        pitchOut = (pitchOut / qAbs(pitchOut)) * 0.6;
    if (qAbs(rollOut) > 0.6)
        rollOut = (rollOut / qAbs(rollOut)) * 0.6;

    // set controls
    aircraft->setElevator(pitchOut);
    aircraft->setAilerons(rollOut);

//    qDebug() << "Pitch " << m_DesiredPitch << "(" << pitch << ")";
}

void FgAutopilot::follow(FgControlledAircraft * aircraft, FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();
    m_DesiredRoll = followAircraft->roll();

    holdAltitude(aircraft);
}
