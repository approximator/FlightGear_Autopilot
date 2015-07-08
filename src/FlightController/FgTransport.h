/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jul 08, 2015
 */

#ifndef FGPROTOCOL_H
#define FGPROTOCOL_H

#include "FgGenericProtocol.h"

#include <memory>
#include <QObject>
#include <QUdpSocket>
#include <QJsonObject>
#include <QHostAddress>

class FgTransport : public QObject
{
    Q_OBJECT
public:
    explicit FgTransport(const QJsonObject& config, QObject *parent = 0);
    ~FgTransport();

    inline QString getString(const QString& node, bool *exists = nullptr) const;
    inline qreal getFloat(const QString& node, bool *exists = nullptr) const;
    inline qint32 getInt(const QString& node, bool *exists = nullptr) const;

    inline std::shared_ptr<FgGenericProtocol> protocol() const;

    bool writeData(const QString& data);
    inline QString networkParams() const;

private:
    std::shared_ptr<QUdpSocket> m_Socket          { std::make_shared<QUdpSocket>() };
    std::shared_ptr<QUdpSocket> m_SocketOut       { std::make_shared<QUdpSocket>() };
    std::shared_ptr<FgGenericProtocol> m_Protocol { std::make_shared<FgGenericProtocol>() };

    bool         m_GenericEnabled       { false };
    QHostAddress m_ListenHost           { "127.0.0.1" };
    quint16      m_ListenPort           { 5555 };
    QString      m_ListenProtocol       { "udp" };
    QString      m_ListenGenericProtocol{ "FgaProtocol" };
    int          m_ListenFrequency      { 40 };
    QHostAddress m_WriteHost            { "127.0.0.1" };
    quint16      m_WritePort            { 5556 };
    QString      m_WriteProtocol        { "udp" };
    QString      m_WriteGenericProtocol { "FgaProtocol" };
    int          m_WriteFrequency       { 40 };
    QByteArray   m_Buffer               { };
    QStringList  m_FdmData              { };

signals:
    void fgDataReceived();

private slots:
    void onSocketRead();

public slots:

    friend class ControlledAircraftTest;
};

//
QString FgTransport::getString(const QString& node, bool *exists) const
{
    int paramIndex = m_Protocol->getParamIndex(node);
    if (paramIndex > -1)
    {
        if (exists)
        {
            *exists = true;
        }
        return m_FdmData[paramIndex]; //! @todo check index
    }

    if (exists)
    {
        *exists = false;
    }
    return "";
}

qreal FgTransport::getFloat(const QString& node, bool *exists) const
{
    QString param = getString(node);
    return param.isEmpty() ? 0.0 : param.toFloat(exists);
}

qint32 FgTransport::getInt(const QString& node, bool *exists) const
{
    QString param = getString(node);
    return param.isEmpty() ? 0 : param.toInt(exists);
}

std::shared_ptr<FgGenericProtocol> FgTransport::protocol() const
{
    return m_Protocol;
}

QString FgTransport::networkParams() const
{
    if (!m_GenericEnabled)
        return "";

    return QString("--generic=socket,out,%1,%2,%3,%4,%5 --generic=socket,in,%6,%7,%8,%9,%10")
            .arg(m_ListenFrequency)
            .arg(m_ListenHost.toString())
            .arg(m_ListenPort)
            .arg(m_ListenProtocol, m_ListenGenericProtocol)
            .arg(m_WriteFrequency)
            .arg(m_WriteHost.toString())
            .arg(m_WritePort)
            .arg(m_WriteProtocol, m_WriteGenericProtocol);
}

#endif // FGPROTOCOL_H
