/*!
 * @file FgFlightgear.h
 * @brief Flightgear system info and actions
 *
 * Every FgControlledAircraft has his own FgFlightgear instance.
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FGFLIGHTGEAR_H
#define FGFLIGHTGEAR_H

#include "FgTransport.h"
#include "utils/Filesystem.h"

#include <QPair>
#include <QFuture>
#include <QProcess>
#include <QSettings>
#include <QFutureWatcher>

#include <memory>

class FgFlightgear : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString rootDir READ rootDir WRITE setRootDir NOTIFY rootDirChanged)
    Q_PROPERTY(QString exeFile READ exeFile WRITE setExeFile NOTIFY exeFileChanged)
public:
    explicit FgFlightgear(QObject *parent = 0);
    ~FgFlightgear();

    bool checkPaths();
    bool run();
    Q_INVOKABLE bool ready() const;

    bool setConfig(QSettings &settings);
    bool saveConfig(QSettings &settings);
    QString runParameters() const;

    inline QString rootDir() const;
    inline void setRootDir(const QString _rootDir);
    inline QString exeFile() const;
    inline void setExeFile(const QString _exeFile);

    inline const QProcess &process() const;
    inline std::shared_ptr<FgTransport> transport() const;

private:
    inline QString multiplayParams() const;

#ifdef Q_OS_WIN
    QString m_ExeFile{ fgap::path::normPath("C:/Program Files/FlightGear/bin/win32/fgfs.exe") };
    QString m_RootDir{ fgap::path::normPath("C:/Program Files/FlightGear/data/") };
    QString m_ProtocolFileName{ fgap::path::normPath("Protocol/FgaProtocol.xml") };
    QString m_ProtocolFile{ fgap::path::join(m_RootDir, m_ProtocolFileName) };
#else
    QString m_ExeFile{ "/usr/games/fgfs" };
    QString m_RootDir{ "/usr/share/games/flightgear" };
    QString m_ProtocolFileName{ "Protocol/FgaProtocol.xml" };
    QString m_ProtocolFile{ fgap::path::join(m_RootDir, m_ProtocolFileName) };
#endif

    // clang-format off
    QFuture<bool>        m_InitFuture        { };
    QFutureWatcher<bool> m_InitFutureWatcher { };
    bool    m_Ready      { false };
    QString m_Callsign   { "(none)" };
    QString m_Airport    { "KSFO" };
    QString m_Runway     { "10L" };
    QString m_Aircraft   { "c172p" };
    QString m_WindowSize { "800x600" };
    QString m_TimeOfDay  { "morning" };
    bool    m_MultiplayEnabled      { true };
    quint16 m_MultiplayPortIn       { 5000 };
    int     m_MultiplayFrequencyIn  { 10 };
    QString m_MultiplayHostIn       { };
    quint16 m_MultiplayPortOut      { 5000 };
    int     m_MultiplayFrequencyOut { 10 };
    QString m_MultiplayHostOut      { };
    QProcess m_FlightgearProcess    { };
    std::shared_ptr<FgTransport>      m_Transport     { std::make_shared<FgTransport>(this) };
    QVector<QPair<QString, QString> > m_RunParameters { };
    // clang-format on

signals:
    /*!
     * @brief readyChanged
     * Emits when init thread finishes his work
     */
    void readyChanged(bool);
    void rootDirChanged();
    void exeFileChanged();

public slots:
    bool init();

    void initFinished();

    friend class ControlledAircraftTest;
};

QString FgFlightgear::rootDir() const { return m_RootDir; }

void FgFlightgear::setRootDir(const QString _rootDir)
{
    if (m_RootDir == _rootDir)
        return;

    m_RootDir      = fgap::path::normPath(_rootDir);
    m_ProtocolFile = fgap::path::join(m_RootDir, m_ProtocolFileName);
    emit rootDirChanged();
}

QString FgFlightgear::exeFile() const { return m_ExeFile; }

void FgFlightgear::setExeFile(const QString _exeFile)
{
    if (m_ExeFile == _exeFile)
        return;

    m_ExeFile = fgap::path::normPath(_exeFile);
    emit exeFileChanged();
}

const QProcess &FgFlightgear::process() const { return m_FlightgearProcess; }

std::shared_ptr<FgTransport> FgFlightgear::transport() const { return m_Transport; }

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

#endif /* FGFLIGHTGEAR_H */
