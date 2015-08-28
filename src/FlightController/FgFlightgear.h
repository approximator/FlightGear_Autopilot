/*!
 * @file FgFlightgear.h
 * @brief Flightgear system info and actions
 *
 * Every FgControlledAircraft has his own FgFlightgear instance.
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Aug 28, 2015
 */

#ifndef FGFLIGHTGEAR_H
#define FGFLIGHTGEAR_H

#include "FgTransport.h"

#include <QPair>
#include <QFuture>
#include <QProcess>
#include <QSettings>
#include <QFutureWatcher>

#include <memory>

class FgFlightgear : public QObject
{
    Q_OBJECT
public:
    explicit FgFlightgear(QObject *parent = 0);
    ~FgFlightgear();

    bool checkPaths();
    bool run();
    Q_INVOKABLE bool ready() const;

    bool setConfig(QSettings& settings);
    bool saveConfig(QSettings& settings);
    QString runParameters() const;

    inline const QProcess& process() const;
    inline std::shared_ptr<FgTransport> transport() const;
private:
    inline QString multiplayParams() const;

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

    QFuture<bool>        m_InitFuture        { };
    QFutureWatcher<bool> m_InitFutureWatcher { };
    bool    m_Ready      { false };
    QString m_Callsign   { "(none)" };
    QString m_Airport    { "KSFO" };
    QString m_Runway     { "10L" };
    QString m_Aircraft   { "c172p" };
    QString m_WindowSize { "800x600" };
    QString m_TimeOfDay  { "morning" };
    bool    m_MultiplayEnabled      { false };
    quint16 m_MultiplayPortIn       { 5000 };
    int     m_MultiplayFrequencyIn  { 10 };
    QString m_MultiplayHostIn       { };
    quint16 m_MultiplayPortOut      { 5000 };
    int     m_MultiplayFrequencyOut { 10 };
    QString m_MultiplayHostOut      { };
    QProcess m_FlightgearProcess    { };
    std::shared_ptr<FgTransport>      m_Transport     { std::make_shared<FgTransport>(this) };
    QVector<QPair<QString, QString> > m_RunParameters { };

signals:
    /*!
     * @brief readyChanged
     * Emits when init thread finishes his work
     */
    void readyChanged(bool);

public slots:
    bool init();

    void initFinished();

    friend class ControlledAircraftTest;
};


const QProcess &FgFlightgear::process() const
{
    return m_FlightgearProcess;
}

std::shared_ptr<FgTransport> FgFlightgear::transport() const
{
    return m_Transport;
}

QString FgFlightgear::multiplayParams() const
{
    if (!m_MultiplayEnabled)
        return "";

    return QString("--multiplay=out,%1,%2,%3 --multiplay=in,%4,%5,%6")
            .arg(m_MultiplayFrequencyOut)
            .arg(m_MultiplayHostOut)
            .arg(m_MultiplayPortOut)
            .arg(m_MultiplayFrequencyIn)
            .arg(m_MultiplayHostIn)
            .arg(m_MultiplayPortIn);
}

#endif // FGFLIGHTGEAR_H
