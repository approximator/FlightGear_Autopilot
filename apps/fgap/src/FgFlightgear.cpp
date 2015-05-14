/*!
 * @file FgFlightgear.cpp
 * @brief Flightgear system info and actions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified May 14, 2015
 */

#include "FgFlightgear.h"

#include <QFile>
#include <QDir>
#include <QProcess>
#include <QDebug>

FgFlightgear::FgFlightgear(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN
    m_ExeFile = "C:\\Program Files\\FlightGear\\bin\\win32\\fgfs.exe";
    m_RootDir = "C:\\Program Files\\FlightGear\\data\\";
    m_ProtocolFileName = "\\Protocol\\FgaProtocol.xml";
    m_ProtocolFile = m_RootDir + m_ProtocolFileName;
#endif

    checkPaths();
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
    qDebug() << "Not implemented yet:    FgFlightgear::run()";
    return false;
}

