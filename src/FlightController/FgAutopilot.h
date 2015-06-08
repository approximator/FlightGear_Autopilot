/*!
 * @file FgAutopilot.h
 *
 * @brief Autopilot to control aircraft
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 14, 2015
 * @date Modified May 05, 2015
 */
#ifndef FGAUTOPILOT_H
#define FGAUTOPILOT_H

#include <memory>
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

    void computeControl(FgControlledAircraft *aircraft);

private:
    AUTOPILOT_MODE m_Mode = FG_MODE_ANGLES_HOLD;

    qreal m_DesiredPitch     = 3.0;    // deg
    qreal m_DesiredRoll      = 0.0;    // deg
    qreal m_DesiredYaw       = 0.0;    // deg
    qreal m_DesiredLongitude = 0.0;    // deg
    qreal m_DesiredLatitude  = 0.0;    // deg
    qreal m_DesiredAltitude  = 1000.0; // ft
    qreal m_DesiredHeading   = 0.0;    // deg

    void holdAltitude(FgControlledAircraft* aircraft);
    void holdAngles(FgControlledAircraft *aircraft);
    void follow(FgControlledAircraft* aircraft);

signals:

public slots:

};

#endif // FGAUTOPILOT_H
