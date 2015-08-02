/*!
 * @file FgFlightgear.cpp
 * @brief Flightgear system info and actions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Aug 03, 2015
 */

#include "log.h"
#include "FgFlightgear.h"

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QJsonArray>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrent>

FgFlightgear::FgFlightgear(const QJsonObject &config, QObject *parent) : QObject(parent)
{
    setConfigFromJson(config);
    init();
}

FgFlightgear::~FgFlightgear()
{
//    m_InitFuture.waitForFinished();
    m_InitFuture.cancel();
}

bool FgFlightgear::init()
{
    LOG(INFO) << "Flightgear init";
    connect(&m_InitFutureWatcher, SIGNAL(finished()), this, SLOT(initFinished()));
    m_InitFuture = QtConcurrent::run(this, &FgFlightgear::checkPaths);
    m_InitFutureWatcher.setFuture(m_InitFuture);
    return true;
}

void FgFlightgear::initFinished()
{
    LOG(INFO) << "Init finished";
    m_Ready = m_InitFuture.result();
    emit readyChanged(m_Ready);
}

bool FgFlightgear::checkPaths()
{
    bool result = true;

    LOG(INFO) << "Checking for Flightgear..." << QThread::currentThread();
    if (!QFile::exists(m_ExeFile))
    {
        LOG(ERROR) << "Flightgear executable does not exist in default location (" << m_ExeFile.toStdString() << ")";
        return false;
    }

    QProcess fgfs;
    fgfs.setProcessChannelMode(QProcess::MergedChannels);
    fgfs.start(m_ExeFile, QStringList() << "--version");
    if (!fgfs.waitForStarted())
    {
        LOG(ERROR) << "Can't start " << m_ExeFile.toStdString();
        return false;
    }

    if (!fgfs.waitForFinished())
    {
        LOG(ERROR) << "ERROR: waitForFinished";
        return false;
    }

    // Read FlightGear output to the string
    QString fgOutput(fgfs.readAll());
    LOG_IF(ERROR, fgOutput.isEmpty()) << "Flightgear output is empty";

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
        LOG(ERROR) << m_RootDir.toStdString() << " does not exist.";
        result = false;
    }

    m_ProtocolFile = m_RootDir + m_ProtocolFileName;

    m_Transport->protocol()->writeXml(m_ProtocolFile);

    LOG(INFO) << "FG_ROOT = " << m_RootDir.toStdString();
    LOG(INFO) << "Protocol file = " << m_ProtocolFile.toStdString();
    return result;
}

bool FgFlightgear::run()
{
    LOG(INFO) << "Running Flightgear";
    if (m_FlightgearProcess.state() != QProcess::NotRunning)
    {
        LOG(ERROR) << "Can't run Flightgear. It is already running.";
        return false;
    }

    LOG(INFO) << "Starting: " << m_ExeFile.toStdString() + ' ' + runParameters().toStdString();
    m_FlightgearProcess.start(m_ExeFile + ' ' + runParameters());

    return true;
}

bool FgFlightgear::ready() const
{
    return m_Ready;
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
    m_Callsign = config["callsign"].toString(m_Callsign);
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

    m_MultiplayEnabled = config["multiplay"].isObject();
    if (m_MultiplayEnabled)
    {
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
    }

    m_RunParameters.clear();
    QJsonObject runParams = config["run_parameters"].toObject();
    for (auto &key : runParams.keys())
        m_RunParameters.push_back(QPair<QString, QString>(key, runParams[key].toString()));

    return true;
}

QString FgFlightgear::runParameters() const
{
    QStringList args;
    for (auto const &param : m_RunParameters)
        args << ("--" + param.first + (param.second.isEmpty() ? "" : ("=" + param.second)));
    QString additionalArguments = args.join(' ');
    QString multiplay = multiplayParams();
    QString network = m_Transport->networkParams();

    QString result = QString("--callsign=%1 --airport=%2 --runway=%3 --aircraft=%4 --geometry=%5 --timeofday=%6").
            arg(m_Callsign, m_Airport, m_Runway, m_Aircraft, m_WindowSize, m_TimeOfDay);
    if (!additionalArguments.isEmpty())
        result.append(' ').append(additionalArguments);
    if (!multiplay.isEmpty())
        result.append(' ').append(multiplay);
    if (!network.isEmpty())
        result.append(' ').append(network);

    return result;
}


