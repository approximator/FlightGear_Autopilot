/*!
 * @file FgTransport.cpp
 *
 * @brief Transport implementation for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 08, 2015
 */

#include "FgTransport.h"
#include "FgGenericProtocol.h"

#include <QDebug>

FgTransport::FgTransport(const QJsonObject &config, QObject *parent) :
    QObject(parent)
{
    if (!config.empty())
    {
        m_GenericEnabled = true;
        QJsonObject in = config["in"].toObject();
        if (!in.empty())
        {
            m_WriteFrequency = in["frequency"].toInt(m_WriteFrequency);
            m_WritePort = in["port"].toInt(m_WritePort);
            m_WriteProtocol = in["protocol"].toString(m_WriteProtocol);
            m_WriteGenericProtocol = in["protocol_file"].toString(m_WriteGenericProtocol);
            QString host = in["host"].toString(m_WriteHost.toString());
            m_WriteHost = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
        }
        QJsonObject out = config["out"].toObject();
        if (!out.empty())
        {
            m_ListenFrequency = out["frequency"].toInt(m_ListenFrequency);
            m_ListenPort = out["port"].toInt(m_ListenPort);
            m_ListenProtocol = out["protocol"].toString(m_ListenProtocol);
            m_ListenGenericProtocol = out["protocol_file"].toString(m_ListenGenericProtocol);
            QString host = out["host"].toString(m_ListenHost.toString());
            m_ListenHost = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
        }
    }

    m_Socket->bind(m_ListenHost, m_ListenPort);
    connect(m_Socket.get(), &QUdpSocket::readyRead, this, &FgTransport::onSocketRead);
    qDebug() << "FgTransport ready [" << m_ListenHost.toString() << ":" << m_ListenPort << "]" << "out: " << m_WritePort;
}

FgTransport::~FgTransport()
{
    qDebug() << "FgTransport destroyed[" << m_ListenHost.toString() << ":" << m_ListenPort << "]" << "out: " << m_WritePort;
}

void FgTransport::onSocketRead()
{
    while (m_Socket->hasPendingDatagrams())
    {
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
        if (newLineIndex < 0)
        {
            return;
        }

        // we have the whole line
        QString line = QString::fromLocal8Bit(m_Buffer.data(), newLineIndex);
        m_FdmData = line.split("\t");
        m_Buffer.remove(0, newLineIndex + 1);

        emit fgDataReceived();
    }
}

bool FgTransport::writeData(const QString &data)
{
    m_SocketOut->writeDatagram(data.toLocal8Bit(), m_WriteHost, m_WritePort);
    return true;
}

