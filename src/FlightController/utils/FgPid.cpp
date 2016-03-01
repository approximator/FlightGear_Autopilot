/*!
 * @file FgPid.cpp
 *
 * @brief PID controller inmplementation
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
#include "FgPid.h"

FgPid::FgPid(double initial_kp, double initial_ki, double initial_kd, double max_output, double initial_int_max)
    : _kp(initial_kp)
    , _ki(initial_ki)
    , _kd(initial_kd)
    , _max_output(max_output)
    , _int_max(initial_int_max)
{
}

double FgPid::update(double error, double dt)
{
    using fgap::math::limit;
    using fgap::math::rungeKutta;
    double p;
    double i;
    double d;

    /* proportional term  */
    p = _kp * error;

    /* integration */
    _int_error += limit(_ki * rungeKutta(dt, error), _int_max);
    i = _int_error;

    /* differentiation */
    if (std::isnan(_prev_d)) {
        d       = 0;
        _prev_d = 0;
    } else
        d = (error - _prev_error) / dt;

    double RC = 1 / (2 * 3.14 * _filter);
    d         = _prev_d + ((dt / (RC + dt)) * (d - _prev_d));

    _prev_d     = d;
    _prev_error = error;
    d           = _kd * d;

    _control = p + i + d;

    /* qDebug() << "p = " << p << "\ti = " << i << "\td = " << d; */

    return limit(_control, _max_output);
}

void FgPid::reset()
{
    _prev_error = 0;
    _int_error  = 0;
    _prev_d     = NAN;
}
