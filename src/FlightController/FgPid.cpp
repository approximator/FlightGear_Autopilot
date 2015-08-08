/*!
 * @file FgPid.cpp
 *
 * @brief PID controller inmplementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 30, 2015
 */

#include "log.h"
#include "FgPid.h"

FgPid::FgPid(double initial_kp, double initial_kd, double initial_ki, double initial_int_max):
    _kp(initial_kp),
    _kd(initial_kd),
    _ki(initial_ki),
    _int_max(initial_int_max)
{

}

double FgPid::update(double error)
{
    double p;
    double i;
    double d;

    // proportional term
    p = _kp * error;

    // integration
    _int_error += _ki * error * _dt;
    _int_error = fgap::math::limit(_int_error, _int_max);
    i = _int_error;

    // differentiation
    if (std::isnan(_prev_d))
    {
        d = 0;
        _prev_d = 0;
    }
    else
        d = (error - _prev_error) / _dt;

    double RC = 1 / (2 * 3.14 * _filter);
    d = _prev_d + ((_dt / (RC + _dt)) * (d - _prev_d));

    _prev_d = d;
    _prev_error = error;
    d = _kd * d;

    _control = p + i + d;

//    qDebug() << "Error = " << error << "Control = " << _control << "(i = " << i << ")";
    return _control;
}

void FgPid::reset()
{
    _prev_error = 0;
    _int_error = 0;
    _prev_d = NAN;
}


