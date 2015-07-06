/*!
 * @file FgFlightgear.cpp
 * @brief Flightgear system info and actions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Jul 05, 2015
 */

#include "FgFlightgear.h"

#include <QFile>
#include <QDir>
#include <QProcess>
#include <QJsonArray>
#include <QDebug>

FgFlightgear::FgFlightgear(QObject *parent) : QObject(parent)
{
    init();
}

FgFlightgear::FgFlightgear(const QJsonObject &config, QObject *parent) : QObject(parent)
{
    setConfigFromJson(config);
    init();
}

bool FgFlightgear::init()
{
    checkPaths();
    return true;
}

bool FgFlightgear::checkPaths()
{
    bool result = true;
    if (!QFile::exists(m_ExeFile))
    {
        qDebug() << "Flightgear executable does not exist in default location (" << m_ExeFile << ")";
        return false;
    }
    qDebug() << "Checking for Flightgear...";

    QProcess fgfs;
    fgfs.setProcessChannelMode(QProcess::MergedChannels);
    fgfs.start(m_ExeFile, QStringList() << "--version");
    if (!fgfs.waitForStarted())
    {
        qDebug() << "Can't start " << m_ExeFile;
        return false;
    }

    if (!fgfs.waitForFinished())
    {
        qDebug() << "ERROR: waitForFinished";
        return false;
    }

    // Read FlightGear output to the string
    QString fgOutput(fgfs.readAll());
    if (fgOutput.isEmpty())
    {
        qDebug() << "Flightgear output is empty";
    }

    // parse output to find Flightgear root directory

    // auto fgVersionToken = "FlightGear version: ";
    // auto fgHomeToken = "FG_HOME=";
    auto fgRootToken = "FG_ROOT=";
    for (auto &str : fgOutput.split('\n'))
    {
        if (str.startsWith(fgRootToken))
        {
            m_RootDir = str.mid(qstrlen(fgRootToken));
        }
    }

    if (!QDir(m_RootDir).exists())
    {
        qDebug() << m_RootDir << " does not exist.";
        result = false;
    }

    m_ProtocolFile = m_RootDir + m_ProtocolFileName;

    qDebug() << "FG_ROOT = " << m_RootDir;
    qDebug() << "Protocol file = " << m_ProtocolFile;
    return result;
}

bool FgFlightgear::run()
{
    qDebug() << "Running Flightgear";
    if (m_FlightgearProcess.state() != QProcess::NotRunning)
    {
        qWarning() << "Can't run Flightgear. It is already running.";
        return false;
    }

    QStringList arguments;
    arguments << multiplayParams();
    arguments << m_Transport->networkParams();
    for (auto const &param : m_RunParameters)
        arguments << ("--" + param.first + (param.second.isEmpty() ? "" : ("=" + param.second)));
    qDebug() << "Starting: " << m_ExeFile << arguments;
    m_FlightgearProcess.start(m_ExeFile, arguments);

    return true;
}

QJsonObject FgFlightgear::configurationAsJson() const
{
    QJsonObject runParameters;
    for (auto &param : m_RunParameters)
        runParameters[param.first] = param.second;

    QJsonObject config;
    config["exe_file"] = m_ExeFile;
    config["protocol_file"] = m_ProtocolFile;
    config["root_directory"] = m_RootDir;
    config["run_parameters"] = runParameters;
    return config;
}

bool FgFlightgear::setConfigFromJson(const QJsonObject &config)
{
    m_ExeFile = config["exe_file"].toString(m_ExeFile);
    m_ProtocolFile = config["protocol_file"].toString(m_ProtocolFile);
    m_RootDir = config["root_directory"].toString(m_RootDir);
    m_Airport = config["airport"].toString(m_Airport);
    m_Runway = config["runway"].toString(m_Runway);
    m_Aircraft = config["aircraft"].toString(m_Aircraft);
    m_WindowSize = config["geometry"].toString(m_WindowSize);
    m_TimeOfDay = config["timeofday"].toString(m_TimeOfDay);

    QJsonObject transport = config["generic"].toObject();
    if (!transport.empty())
    {
        m_Transport = std::make_shared<FgTransport>(transport);
    }

    QJsonObject multiplay_in = config["multiplay"].toObject()["in"].toObject();
    if (!multiplay_in.empty())
    {
        m_MultiplayPortIn = multiplay_in["port"].toInt(m_MultiplayPortIn);
        m_MultiplayFrequencyIn = multiplay_in["frequency"].toInt(m_MultiplayFrequencyIn);
        m_MultiplayHostIn = multiplay_in["host"].toString(m_MultiplayHostIn);
    }
    QJsonObject multiplay_out = config["multiplay"].toObject()["out"].toObject();
    if (!multiplay_in.empty())
    {
        m_MultiplayPortOut = multiplay_out["port"].toInt(m_MultiplayPortOut);
        m_MultiplayFrequencyOut = multiplay_out["frequency"].toInt(m_MultiplayFrequencyOut);
        m_MultiplayHostOut = multiplay_out["host"].toString(m_MultiplayHostOut);
    }

    m_RunParameters.clear();
    QJsonObject runParams = config["run_parameters"].toObject();
    for (auto &key : runParams.keys())
        m_RunParameters.push_back(QPair<QString, QString>(key, runParams[key].toString()));

    return true;
}


