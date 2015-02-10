/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Feb 10, 2015
 */

#ifndef FGPROTOCOL_H
#define FGPROTOCOL_H

#include "FgGenericProtocol.h"

#include <QObject>
#include <QHostAddress>

class QUdpSocket;

class FgTransport : public QObject
{
    Q_OBJECT
public:
    explicit FgTransport(QObject *parent = 0);
    ~FgTransport();

    inline QString getString(const QString& node, bool *exists = 0) const;
    inline qreal getFloat(const QString& node, bool *exists = 0) const;
    inline qint32 getInt(const QString& node, bool *exists = 0) const;

    inline FgGenericProtocol* protocol() const;

private:
    QUdpSocket *m_Socket;
    FgGenericProtocol *m_Protocol;

    QHostAddress m_Ip;
    quint16 m_Port;
    QByteArray m_Buffer;
    QStringList m_FdmData;

signals:
    void fgDataReceived();

public slots:

private slots:
    void onSocketRead();
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

FgGenericProtocol *FgTransport::protocol() const
{
    return m_Protocol;
}

#endif // FGPROTOCOL_H
