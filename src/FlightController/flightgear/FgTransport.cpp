/*!
 * @file FgTransport.cpp
 *
 * @brief Transport implementation for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 24, 2016
 */

#include "log.h"
#include "FgTransport.h"
#include "FgGenericProtocol.h"

FgTransport::FgTransport(QObject *parent) : QObject(parent)
{
}

FgTransport::~FgTransport()
{
    //    qDebug() << "FgTransport destroyed[" << m_ListenHost.toString() << ":" << m_ListenPort << "]" << "out: " <<
    //    m_WritePort;
}

bool FgTransport::setConfig(QSettings &settings)
{
    m_GenericEnabled = settings.value("enabled", false).toBool();
    settings.beginGroup("in");
    m_WriteFrequency       = settings.value("frequency").toInt();
    m_WritePort            = settings.value("port").toInt();
    m_WriteProtocol        = settings.value("protocol").toString();
    m_WriteGenericProtocol = settings.value("generic_protocol").toString();
    QString host           = settings.value("host").toString();
    m_WriteHost = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
    settings.endGroup();

    settings.beginGroup("out");
    m_ListenFrequency       = settings.value("frequency").toInt();
    m_ListenPort            = settings.value("port").toInt();
    m_ListenProtocol        = settings.value("protocol").toString();
    m_ListenGenericProtocol = settings.value("generic_protocol").toString();
    host                    = settings.value("host").toString();
    m_ListenHost = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
    settings.endGroup();

    if (!m_GenericEnabled)
        return true;

    m_Socket->bind(m_ListenHost, m_ListenPort);
    connect(m_Socket.get(), &QUdpSocket::readyRead, this, &FgTransport::onSocketRead);
    qDebug() << "FgTransport ready [" << m_ListenHost.toString() << ":" << m_ListenPort << "]"
             << "out: " << m_WritePort;
    return true;
}

bool FgTransport::saveConfig(QSettings &settings)
{
    settings.setValue("enabled", m_GenericEnabled);
    settings.beginGroup("in");
    settings.setValue("frequency", m_WriteFrequency);
    settings.setValue("port", m_WritePort);
    settings.setValue("protocol", m_WriteProtocol);
    settings.setValue("generic_protocol", m_WriteGenericProtocol);
    settings.setValue("host", m_WriteHost.toString());
    settings.endGroup();

    settings.beginGroup("out");
    settings.setValue("frequency", m_ListenFrequency);
    settings.setValue("port", m_ListenPort);
    settings.setValue("protocol", m_ListenProtocol);
    settings.setValue("generic_protocol", m_ListenGenericProtocol);
    settings.setValue("host", m_ListenHost.toString());
    settings.endGroup();
    return true;
}

void FgTransport::onSocketRead()
{
    //    qDebug() << "onSocketRead";
    while (m_Socket->hasPendingDatagrams()) {
        {
            QByteArray datagram;
            datagram.resize(m_Socket->pendingDatagramSize());

            QHostAddress sender;
            quint16 senderPort;
            m_Socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            // we will process only whole line
            // add datagram to buffer
            m_Buffer.append(datagram);
        }

        int newLineIndex = m_Buffer.indexOf('\n', 0);
        if (newLineIndex < 0) {
            return;
        }

        // we have the whole line
        QString line = QString::fromLocal8Bit(m_Buffer.data(), newLineIndex);
        m_FdmData = line.split("\t");
        m_Buffer.remove(0, newLineIndex + 1);

        emit fgDataReceived(this);
    }
}

bool FgTransport::writeData(const QString &data)
{
    m_SocketOut->writeDatagram(data.toLocal8Bit(), m_WriteHost, m_WritePort);
    return true;
}
