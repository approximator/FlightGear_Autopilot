/*!
 * @file FgPid.h
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

#ifndef FGPID_H
#define FGPID_H

#include "FgMath.h"

class FgPid
{
public:
    FgPid(double initial_kp, double initial_ki, double initial_kd, double max_output = 100, double initial_int_max = 5);
    double update(double error, double dt);
    void reset();

private:
    double _kp = 1;
    double _ki = 0.0;
    double _kd = 0.0;

    double _max_output = 100;
    double _int_max    = 5;

    double _prev_error = 0;
    double _prev_d     = NAN;
    double _int_error  = 0;
    double _control    = 0;
    int _filter        = 20;
};

#endif /* FGPID_H */
