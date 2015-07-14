/*!
 * @file FgPid.h
 *
 * @brief PID controller inmplementation
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jul 14, 2015
 * @date Modified Jul 14, 2015
 */

#ifndef FGPID_H
#define FGPID_H

class FgPid
{
public:
    FgPid(double initial_kp, double initial_kd, double initial_ki);
    double update(double error);
    void reset();

private:
    double _kp = 1;
    double _kd = 0.0;
    double _ki = 0.0;
    double _dt = 1;
    double prev_error = 0;
    double int_error = 0;
    double control = 0;
};

#endif // FGPID_H
