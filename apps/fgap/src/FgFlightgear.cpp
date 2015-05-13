/*!
 * @file FgFlightgear.cpp
 * @brief Flightgear system info and actions
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created May 12, 2015
 * @date Modified May 12, 2015
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
    m_DataDir = "C:\\Program Files\\FlightGear\\data\\";
    m_ProtocolFile = m_DataDir + "\\Protocol\\FgaProtocol.xml";
#endif
    checkPaths();
}

bool FgFlightgear::checkPaths()
{
    bool result = true;
    if (!QFile::exists(m_ExeFile))
    {
        qDebug() << "Flightgear executable does not exist in default location (" << m_ExeFile << ")";
        result = false;
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
    qDebug() << fgfs.readAll();

    //! @todo check directories

    return result;
}

bool FgFlightgear::run()
{
    qDebug() << "Not implemented yet:    FgFlightgear::run()";
    return false;
}

