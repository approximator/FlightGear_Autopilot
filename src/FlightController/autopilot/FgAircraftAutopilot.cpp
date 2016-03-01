/*!
 * @file FgAutopilot.cpp
 *
 * @brief Autopilot implementation to control aircraft
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "log.h"
#include "FgAircraftAutopilot.h"
#include "vehicle/FgControlledAircraft.h"

FgAircraftAutopilot::FgAircraftAutopilot(FgControlledAircraft *aircraft, QObject *parent)
    : FgAutopilot(parent)
{
    m_Aircraft = aircraft;
    qDebug() << "Autopilot created";
}

void FgAircraftAutopilot::computeControl()
{
    if (!engaged())
        return;

    /* do not allow autopilot to go crazy with small doubles */
    if (m_Aircraft->delta_time() < 0.00001) {
        /* qWarning() << "Autopilot: Delta time is too small, giving up..."; */
        return;
    }

    /* just stabilize for the first 20 seconds of flight */
    if (m_Aircraft->elapsed_time() < 20) {
        holdAngles();
        return;
    }

    m_ControlFunc();
}

void FgAircraftAutopilot::holdYawRate()
{
    const qreal yawRateError = m_DesiredYawRate - m_Aircraft->yaw_rate();
    m_DesiredRoll = m_YawRatePid.update(yawRateError, m_Aircraft->delta_time());
    holdAltitude();
}

void FgAircraftAutopilot::holdHeading()
{
    qreal headingError = fgap::math::headingOffset(m_Aircraft->heading(), m_DesiredHeading);
    m_DesiredYawRate = fgap::math::limit(headingError * 1, 5.0);
    holdYawRate();
}

void FgAircraftAutopilot::holdVerticalSpeed()
{
    const qreal vsError = m_DesiredVerticalSpeed - m_Aircraft->vertical_speed();
    m_DesiredPitch      = m_VerticalSpeedPid.update(vsError, m_Aircraft->delta_time());

    holdAngles();

    /* For Debug only
    qDebug() << "    Yaw rate = " << m_Aircraft->yawRate() << "/" << m_DesiredYawRate;
    qDebug() << "     Heading = " << m_Aircraft->heading() << "/" << m_DesiredHeading;
    */
}

void FgAircraftAutopilot::holdAltitude()
{
    qreal altitudeError    = m_DesiredAltitude - m_Aircraft->altitude();
    m_DesiredVerticalSpeed = fgap::math::limit(altitudeError * 0.8, 25.0);
    holdVerticalSpeed();
}

void FgAircraftAutopilot::holdAngles()
{
    qreal pitch = m_Aircraft->pitch();
    qreal roll  = m_Aircraft->roll();

    qreal pitchError = pitch - m_DesiredPitch;
    qreal rollError  = m_DesiredRoll - roll;

    /* Set controls */
    m_Aircraft->set_elevator(m_PitchPid.update(pitchError, m_Aircraft->delta_time()));
    m_Aircraft->set_ailerons(m_RollPid.update(rollError, m_Aircraft->delta_time()));

    /* For Debug only
    qDebug() << "Elapsed time = " << m_Aircraft->elapsedTime();
    qDebug() << "  Delta time = " << m_Aircraft->deltaTime();
    qDebug() << "          VS = " << m_Aircraft->verticalSpeed() << "/" << m_DesiredVerticalSpeed;
    qDebug() << "       Pitch = " << m_Aircraft->pitch() << "/" << m_DesiredPitch;
    qDebug() << "        Roll = " << m_Aircraft->roll() << "/" << m_DesiredRoll;
    */
}

void FgAircraftAutopilot::follow(FgAircraft *followAircraft)
{
    m_DesiredAltitude = followAircraft->altitude();

    m_DesiredHeading = fgap::math::headingTo(
        m_Aircraft->latitude(), m_Aircraft->longitude(), followAircraft->latitude(), followAircraft->longitude());

    holdHeading();
}
