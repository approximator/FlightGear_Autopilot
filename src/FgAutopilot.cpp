/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Feb 14, 2015
 */
#include "FgAutopilot.h"
#include "FgAircraft.h"

FgAutopilot::FgAutopilot(QObject *parent) :
    QObject(parent),
    m_Mode(FG_MODE_ANGLES_HOLD),
    m_DesiredPitch(0.0),
    m_DesiredRoll(0.0),
    m_DesiredYaw(0.0),
    m_DesiredLongitude(0.0),
    m_DesiredLatitude(0.0),
    m_DesiredAltitude(1000.0),
    m_DesiredHeading(0.0)
{
}

void FgAutopilot::computeControl(FgAircraft *aircraft)
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

void FgAutopilot::holdAltitude(FgAircraft * /* aircraft */)
{

}

void FgAutopilot::holdAngles(FgAircraft * /* aircraft */)
{

}

void FgAutopilot::follow(FgAircraft * /* aircraft */)
{

}
