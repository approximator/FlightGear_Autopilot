/*!
 * @file FgFlightgear.h
 * @brief Flightgear system info and actions
 *
 * Every FgControlledAircraft has his own FgFlightgear instance.
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Jun 30, 2015
 */

#ifndef FGFLIGHTGEAR_H
#define FGFLIGHTGEAR_H

#include <memory>
#include <QObject>
#include <QProcess>
#include <QJsonObject>

class FgFlightgear : public QObject
{
    Q_OBJECT
public:
    explicit FgFlightgear(QObject *parent = 0);
    explicit FgFlightgear(const QJsonObject& config, QObject *parent = 0);

    bool init();
    bool checkPaths();
    bool run();

    bool setConfigFromJson(const QJsonObject& config);

private:
    QString m_ExeFile { "/usr/games/fgfs" };
    QString m_RootDir { "/usr/share/games/flightgear" };
    QString m_ProtocolFileName { "/Protocol/FgaProtocol.xml" };
    QString m_ProtocolFile { m_RootDir +  m_ProtocolFileName };
    QProcess m_FlightgearProcess {};

signals:

public slots:
};

#endif // FGFLIGHTGEAR_H
