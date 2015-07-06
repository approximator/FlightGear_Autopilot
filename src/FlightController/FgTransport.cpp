/*!
 * @file FgTransport.cpp
 *
 * @brief Transport implementation for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 05, 2015
 */

#include "FgTransport.h"
#include "FgGenericProtocol.h"

#include <QDebug>

FgTransport::FgTransport(quint16 _port_in, quint16 _port_out, QObject *parent) :
    QObject(parent)
{
    m_ListenPort = _port_out;
    m_WritePort = _port_in;
    m_Socket->bind(QHostAddress::Any, m_ListenPort);
    connect(m_Socket.get(), &QUdpSocket::readyRead, this, &FgTransport::onSocketRead);
    qDebug() << "FgTransport ready [" << m_Ip.toString() << ":" << m_ListenPort << "]" << "out: " << m_WritePort;
}

FgTransport::~FgTransport()
{
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
    m_SocketOut->writeDatagram(data.toLocal8Bit(), m_Ip, m_WritePort);
    return true;
}

