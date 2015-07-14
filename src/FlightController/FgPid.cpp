/*!
 * @file FgPid.cpp
 *
 * @brief PID controller inmplementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 14, 2015
 */

#include "FgPid.h"

#include <QDebug>

FgPid::FgPid(double initial_kp, double initial_kd, double initial_ki):
    _kp(initial_kp),
    _kd(initial_kd),
    _ki(initial_ki)
{

}

double FgPid::update(double error)
{
    // integration
    int_error += (error * _dt);
    // limit

    // differentiation
    double diff = ((error - prev_error) / _dt);

    double p = (_kp * error);
    double i = (_ki * int_error);
    double d = (_kd * diff);

    control = p + i + d;

    qDebug() << "Error = " << error << "Control = " << control << "(i = " << i << ")";
    prev_error = error;

    return control;
}

void FgPid::reset()
{
    prev_error = 0;
    int_error = 0;
}


