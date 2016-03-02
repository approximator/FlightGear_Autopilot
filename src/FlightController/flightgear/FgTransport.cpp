/*!
 * @file FgTransport.cpp
 *
 * @brief Transport implementation for interacting with FlightGear
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

#include "FgTransport.h"
#include "FgGenericProtocol.h"
#include "log.h"

FgTransport::FgTransport(QObject *parent)
    : QObject(parent)
{
}

FgTransport::~FgTransport()
{
    /* Debug only
    qDebug() << "FgTransport destroyed["
             << m_ListenHost.toString()
             << ":" << m_ListenPort << "]"
             << "out: " << m_WritePort;
    */
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
    m_WriteHost            = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
    settings.endGroup();

    settings.beginGroup("out");
    m_ListenFrequency       = settings.value("frequency").toInt();
    m_ListenPort            = settings.value("port").toInt();
    m_ListenProtocol        = settings.value("protocol").toString();
    m_ListenGenericProtocol = settings.value("generic_protocol").toString();
    host                    = settings.value("host").toString();
    m_ListenHost            = QHostAddress(host.toLower() == "localhost" ? "127.0.0.1" : host);
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
    /*    qDebug() << "onSocketRead"; */
    while (m_Socket->hasPendingDatagrams()) {
        {
            QByteArray datagram;
            datagram.resize(m_Socket->pendingDatagramSize());

            QHostAddress sender;
            quint16 senderPort;
            m_Socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

            /* we will process only whole line
             * add datagram to buffer */
            m_Buffer.append(datagram);
        }

        int newLineIndex = m_Buffer.indexOf('\n', 0);
        if (newLineIndex < 0) {
            return;
        }

        /* we have the whole line */
        QString line = QString::fromLocal8Bit(m_Buffer.data(), newLineIndex);
        m_FdmData    = line.split("\t");
        m_Buffer.remove(0, newLineIndex + 1);

        emit fgDataReceived(this);
    }
}

bool FgTransport::writeData(const QString &data)
{
    m_SocketOut->writeDatagram(data.toLocal8Bit(), m_WriteHost, m_WritePort);
    return true;
}
