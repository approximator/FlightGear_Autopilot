/*!
 * @file FgTransport.cpp
 *
 * @brief Transport implementation for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#include "FgTransport.h"
#include "FgGenericProtocol.h"

#include <QUdpSocket>
#include <QDebug>

FgTransport::FgTransport(QObject *parent) :
    QObject(parent),
    m_Socket(0),
    m_Protocol(0),
    m_Ip("127.0.0.1"),
    m_Port(5555)
{
    m_Protocol = new FgGenericProtocol(this);
    m_Protocol->writeXml("/usr/share/games/flightgear/Protocol/FgaOut.xml");

    m_Socket = new QUdpSocket(this);
    m_Socket->bind(QHostAddress::Any, 5555);

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(onSocketRead()));

    qDebug() << "FgTransport ready [" << m_Ip << ":" << m_Port << "]";
}

FgTransport::~FgTransport()
{
    qDebug() << "FgTransport destroyed.";
}

void FgTransport::onSocketRead()
{
    while (m_Socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_Socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_Socket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        qDebug() << datagram;
        //processTheDatagram(datagram);
    }
}

/*

# How to run multiplayer

/usr/games/fgfs \
  --airport=KSFO \
  --runway=10L \
  --aircraft=c172p \
  --console \
  --bpp=32 \
  --disable-random-objects \
  --disable-ai-models \
  --disable-ai-traffic \
  --disable-real-weather-fetch \
  --geometry=1366x768 \
  --timeofday=morning \
  --enable-terrasync \
  --enable-clouds3d \
  --enable-horizon-effect \
  --enable-enhanced-lighting \
  --callsign=App1 \
  --multiplay=out,10,mpserver02.flightgear.org,5000 \
  --multiplay=in,10,,5000 \
  --httpd=5050 \
  --generic=socket,out,40,localhost,5555,udp,FgaOut --generic=socket,in,45,localhost,5010,udp,FgaIn
*/

