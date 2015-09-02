/*!
 * @file FgFlightgear.cpp
 * @brief Flightgear system info and actions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified Sep 02, 2015
 */

#include "log.h"
#include "FgFlightgear.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QtConcurrent/QtConcurrent>

#include <tuple>

FgFlightgear::FgFlightgear(QObject *parent) : QObject(parent)
{

}

FgFlightgear::~FgFlightgear()
{
//    m_InitFuture.waitForFinished();
    m_InitFuture.cancel();
}

bool FgFlightgear::init()
{
    qDebug() << "Flightgear init";
    connect(&m_InitFutureWatcher, SIGNAL(finished()), this, SLOT(initFinished()));
    m_InitFuture = QtConcurrent::run(this, &FgFlightgear::checkPaths);
    m_InitFutureWatcher.setFuture(m_InitFuture);
    return true;
}

void FgFlightgear::initFinished()
{
    qDebug() << "Init finished";
    m_Ready = m_InitFuture.result();
    emit readyChanged(m_Ready);
}

bool FgFlightgear::checkPaths()
{
    bool result = true;

    qDebug() << "Checking for Flightgear..." << QThread::currentThread();
    if (!QFile::exists(m_ExeFile))
    {
        qWarning() << "Flightgear executable does not exist in default location (" << m_ExeFile << ")";
        return false;
    }

//    QProcess fgfs;
//    fgfs.setProcessChannelMode(QProcess::MergedChannels);
//    fgfs.start(m_ExeFile, QStringList() << "--version");
//    if (!fgfs.waitForStarted())
//    {
//        qWarning() << "Can't start " << m_ExeFile;
//        return false;
//    }

//    if (!fgfs.waitForFinished())
//    {
//        qWarning() << "ERROR: waitForFinished";
//        return false;
//    }

//    // Read FlightGear output to the string
//    QString fgOutput(fgfs.readAll());
//    qWarning() << (fgOutput.isEmpty() ? "Flightgear output is empty" : "Read Flightgear output, OK." );

//    // parse output to find Flightgear root directory

//    // auto fgVersionToken = "FlightGear version: ";
//    // auto fgHomeToken = "FG_HOME=";
//    auto fgRootToken = "FG_ROOT=";
//    for (auto &str : fgOutput.split('\n'))
//    {
//        if (str.startsWith(fgRootToken))
//        {
//            m_RootDir = str.mid(qstrlen(fgRootToken));
//        }
//    }

    if (!QDir(m_RootDir).exists())
    {
        qWarning() << m_RootDir << " does not exist.";
        result = false;
    }

    m_ProtocolFile = m_RootDir + m_ProtocolFileName;

    result = m_Transport->protocol()->writeXml(m_ProtocolFile);

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

    qDebug() << "Starting: " << m_ExeFile + ' ' + runParameters();
    m_FlightgearProcess.start(m_ExeFile + ' ' + runParameters());

    return true;
}

bool FgFlightgear::ready() const
{
    return m_Ready;
}

bool FgFlightgear::setConfig(QSettings& settings)
{
    m_Callsign = settings.value("callsign").toString();
    m_ExeFile = settings.value("exe_file", m_ExeFile).toString();
    m_ProtocolFile = settings.value("protocol_file", m_ProtocolFile).toString();
    m_RootDir = settings.value("root_directory", m_RootDir).toString();
    m_Airport = settings.value("airport", m_Airport).toString();
    m_Runway = settings.value("runway", m_Runway).toString();
    m_Aircraft = settings.value("aircraft", m_Aircraft).toString();
    m_WindowSize = settings.value("geometry", m_WindowSize).toString();
    m_TimeOfDay = settings.value("timeofday", m_TimeOfDay).toString();

    settings.beginGroup("generic");
    m_Transport->setConfig(settings);
    settings.endGroup();

    settings.beginGroup("multiplay");
    m_MultiplayEnabled = settings.value("enabled", false).toBool();
    if (m_MultiplayEnabled)
    {
        auto getMultiplayParams = [](QSettings& settings, const QString& group) {
            settings.beginGroup(group);
            int frequency = settings.value("frequency").toInt();
            QString host = settings.value("host").toString();
            int port = settings.value("port").toInt();
            settings.endGroup();
            return std::make_tuple(frequency, host, port);
        };
        std::tie(m_MultiplayPortIn, m_MultiplayHostIn, m_MultiplayFrequencyIn) = getMultiplayParams(settings, "in");
        std::tie(m_MultiplayPortOut, m_MultiplayHostOut, m_MultiplayFrequencyOut) = getMultiplayParams(settings, "out");
    }
    settings.endGroup();

    m_RunParameters.clear();
    settings.beginGroup("additional_parameters");
    QStringList keys = settings.allKeys();
    for (auto &key : keys)
        m_RunParameters.push_back(QPair<QString, QString>(key, settings.value(key).toString()));
    settings.endGroup();
    return true;
}

bool FgFlightgear::saveConfig(QSettings &settings)
{
    settings.setValue("callsign", m_Callsign);
    settings.setValue("exe_file", m_ExeFile);
    settings.setValue("protocol_file", m_ProtocolFile);
    settings.setValue("root_directory", m_RootDir);
    settings.setValue("airport", m_Airport);
    settings.setValue("runway", m_Runway);
    settings.setValue("aircraft", m_Aircraft);
    settings.setValue("geometry", m_WindowSize);
    settings.setValue("timeofday", m_TimeOfDay);
    settings.beginGroup("generic");
    m_Transport->saveConfig(settings);
    settings.endGroup();

    settings.beginGroup("multiplay");
    settings.setValue("enabled", m_MultiplayEnabled);
    auto setMultiplayParams = [&settings](const QString& group, int frequency, const QString& host, int port) {
        settings.beginGroup(group);
        settings.setValue("frequency", frequency);
        settings.setValue("host", host);
        settings.setValue("port", port);
        settings.endGroup();
    };
    setMultiplayParams("in", m_MultiplayFrequencyIn, m_MultiplayHostIn, m_MultiplayPortIn);
    setMultiplayParams("out", m_MultiplayFrequencyOut, m_MultiplayHostOut, m_MultiplayPortOut);
    settings.endGroup();

    settings.beginGroup("additional_parameters");
    for (auto const &param : m_RunParameters)
        settings.setValue(param.first, param.second);
    settings.endGroup();

    return true;
}

QString FgFlightgear::runParameters() const
{
    QStringList args;
    args << "--fg-root=" + m_RootDir;
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


