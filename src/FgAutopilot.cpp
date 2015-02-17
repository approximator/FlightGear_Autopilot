/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Feb 17, 2015
 */
#include "FgAutopilot.h"
#include "FgControlledAircraft.h"

#include <QDebug>

FgAutopilot::FgAutopilot(QObject *parent) :
    QObject(parent),
    m_Mode(FG_MODE_ANGLES_HOLD),
    m_DesiredPitch(10.0),
    m_DesiredRoll(0.0),
    m_DesiredYaw(0.0),
    m_DesiredLongitude(0.0),
    m_DesiredLatitude(0.0),
    m_DesiredAltitude(1000.0),
    m_DesiredHeading(0.0)
{
}

void FgAutopilot::computeControl(FgControlledAircraft *aircraft)
{
    switch (m_Mode)
    {
    case FG_MODE_ALTITUDE_HOLD:
        holdAltitude(aircraft);
        break;
    case FG_MODE_ANGLES_HOLD:
        holdAngles(aircraft);
        break;
    case FG_MODE_FOLLOW:
        follow(aircraft);
        break;
    default:
        break;
    }
}

void FgAutopilot::holdAltitude(FgControlledAircraft * /* aircraft */)
{

}

void FgAutopilot::holdAngles(FgControlledAircraft * aircraft)
{
    qreal pitch = aircraft->pitch();
    qreal roll = aircraft->roll();

    // simple proportional control
    //! @todo improve this
    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError = roll - m_DesiredRoll;

    qreal pitchOut = pitchError * 0.05;
    qreal rollOut = -1 * rollError * 0.05;

    // limit control outputs
    if (qAbs(pitchOut) > 0.6)
        pitchOut = (pitchOut / qAbs(pitchOut)) * 0.6;
    if (qAbs(rollOut) > 0.6)
        rollOut = (rollOut / qAbs(rollOut)) * 0.6;

    // set controls
    aircraft->setElevator(pitchOut);
    aircraft->setAilerons(rollOut);

//    qDebug() << "Autopilot ready";
}

void FgAutopilot::follow(FgControlledAircraft * /* aircraft */)
{

}
