/*!
 * @file FgPid.h
 *
 * @brief PID controller inmplementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Aug 12, 2015
 */

#ifndef FGPID_H
#define FGPID_H

#include "FgMath.h"

class FgPid
{
public:
    FgPid(double initial_kp, double initial_kd, double initial_ki, double initial_int_max = 5);
    double update(double error);
    void reset();

private:
    double _kp = 1;
    double _kd = 0.0;
    double _ki = 0.0;
    double _dt = 1;

    double _int_max = 5;

    double _prev_error = 0;
    double _prev_d = NAN;
    double _int_error = 0;
    double _control = 0;
    int _filter = 20;
};

#endif // FGPID_H
