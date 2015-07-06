/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified May 05, 2015
 */

#ifndef FGPROTOCOL_H
#define FGPROTOCOL_H

#include "FgGenericProtocol.h"

#include <memory>
#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>

class FgTransport : public QObject
{
    Q_OBJECT
public:
    explicit FgTransport(quint16 _port_in = 5555, quint16 _port_out = 5556, QObject *parent = 0);
    ~FgTransport();

    inline QString getString(const QString& node, bool *exists = nullptr) const;
    inline qreal getFloat(const QString& node, bool *exists = nullptr) const;
    inline qint32 getInt(const QString& node, bool *exists = nullptr) const;

    inline std::shared_ptr<FgGenericProtocol> protocol() const;

    bool writeData(const QString& data);

private:
    std::shared_ptr<QUdpSocket> m_Socket          { std::make_shared<QUdpSocket>() };
    std::shared_ptr<QUdpSocket> m_SocketOut       { std::make_shared<QUdpSocket>() };
    std::shared_ptr<FgGenericProtocol> m_Protocol { std::make_shared<FgGenericProtocol>() };

    QHostAddress m_Ip     { "127.0.0.1" };
    quint16 m_ListenPort  { 5555 };
    quint16 m_WritePort   { 5556 };
    QByteArray m_Buffer   { };
    QStringList m_FdmData { };

signals:
    void fgDataReceived();

private slots:
    void onSocketRead();

public slots:
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

#endif // FGPROTOCOL_H
