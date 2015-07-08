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
class FgAircraft;

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

    inline void arm();
    inline void disarm();
    inline bool armed() const;

    inline void setFollow(FgAircraft *aircraft);

    void computeControl(FgControlledAircraft *aircraft);

private:
    AUTOPILOT_MODE m_Mode = FG_MODE_ALTITUDE_HOLD;

    qreal m_DesiredPitch     = 3.0;    // deg
    qreal m_DesiredRoll      = 0.0;    // deg
    qreal m_DesiredYaw       = 0.0;    // deg
    qreal m_DesiredLongitude = 0.0;    // deg
    qreal m_DesiredLatitude  = 0.0;    // deg
    qreal m_DesiredAltitude  = 2000.0; // ft
    qreal m_DesiredHeading   = 0.0;    // deg

    FgAircraft *m_toFollow { nullptr };

    bool m_Armed { false };

    void holdAltitude(FgControlledAircraft* aircraft);
    void holdAngles(FgControlledAircraft *aircraft);
    void follow(FgControlledAircraft* aircraft, FgAircraft *followAircraft);

signals:

public slots:

};

void FgAutopilot::arm()
{
    m_Armed = true;
}

void FgAutopilot::disarm()
{
    m_Armed = false;
}

bool FgAutopilot::armed() const
{
    return m_Armed;
}

void FgAutopilot::setFollow(FgAircraft *aircraft)
{
    m_toFollow = aircraft;
    m_Mode = FG_MODE_FOLLOW;
}

#endif // FGAUTOPILOT_H
