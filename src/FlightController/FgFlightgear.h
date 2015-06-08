/*!
 * @file FgFlightgear.h
 * @brief Flightgear system info and actions
 *
 * Every FgControlledAircraft has his own FgFlightgear instance.
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified May 14, 2015
 */

#ifndef FGFLIGHTGEAR_H
#define FGFLIGHTGEAR_H

#include <QObject>

class FgFlightgear : public QObject
{
    Q_OBJECT
public:
    explicit FgFlightgear(QObject *parent = 0);

    bool checkPaths();
    bool run();

private:
    QString m_ExeFile { "/usr/games/fgfs" };
    QString m_RootDir { "/usr/share/games/flightgear" };
    QString m_ProtocolFileName { "/Protocol/FgaProtocol.xml" };
    QString m_ProtocolFile { m_RootDir +  m_ProtocolFileName };

signals:

public slots:
};

#endif // FGFLIGHTGEAR_H
