/*!
 * @file FgFlightgear.h
 * @brief Flightgear system info and actions
 *
 * Every FgControlledAircraft has his own FgFlightgear instance.
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Jul 05, 2015
 */

#ifndef FGFLIGHTGEAR_H
#define FGFLIGHTGEAR_H

#include <memory>
#include <QVector>
#include <QPair>
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

    QJsonObject configurationAsJson() const;
    bool setConfigFromJson(const QJsonObject& config);

    inline const QProcess& process() const;

private:
#ifdef Q_OS_WIN
    QString m_ExeFile { "C:\\Program Files\\FlightGear\\bin\\win32\\fgfs.exe" };
    QString m_RootDir { "C:\\Program Files\\FlightGear\\data\\" };
    QString m_ProtocolFileName { "\\Protocol\\FgaProtocol.xml" };
    QString m_ProtocolFile { m_RootDir + m_ProtocolFileName };
#else
    QString m_ExeFile { "/usr/games/fgfs" };
    QString m_RootDir { "/usr/share/games/flightgear" };
    QString m_ProtocolFileName { "/Protocol/FgaProtocol.xml" };
    QString m_ProtocolFile { m_RootDir +  m_ProtocolFileName };
#endif

    QVector<QPair<QString, QString> > m_RunParameters { };
    QProcess m_FlightgearProcess {};

signals:

public slots:
};

//
const QProcess &FgFlightgear::process() const
{
    return m_FlightgearProcess;
}

#endif // FGFLIGHTGEAR_H
