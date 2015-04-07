/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified Feb 17, 2015
 */
#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include <QObject>

class FgControlledAircraft;

class FgAutopilot : public QObject
{
    Q_OBJECT
public:
    typedef enum
    {
        FG_MODE_ALTITUDE_HOLD,
        FG_MODE_ANGLES_HOLD,
        FG_MODE_FOLLOW
    } AUTOPILOT_MODE;

    explicit FgAutopilot(QObject *parent = 0);

    void computeControl(FgControlledAircraft* aircraft);

private:
    AUTOPILOT_MODE m_Mode;

    qreal m_DesiredPitch;      // deg
    qreal m_DesiredRoll;       // deg
    qreal m_DesiredYaw;        // deg
    qreal m_DesiredLongitude;  // deg
    qreal m_DesiredLatitude;   // deg
    qreal m_DesiredAltitude;   // ft
    qreal m_DesiredHeading;    // deg

    void holdAltitude(FgControlledAircraft* aircraft);
    void holdAngles(FgControlledAircraft *aircraft);
    void follow(FgControlledAircraft* aircraft);

signals:

public slots:

};

#endif // FGAUTOPILOT_H