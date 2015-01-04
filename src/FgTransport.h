/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 04, 2015
 */

#ifndef FGPROTOCOL_H
#define FGPROTOCOL_H

#include "FgGenericProtocol.h"

#include <QObject>
#include <QHostAddress>

class QUdpSocket;
class FgGenericProtocol;

class FgTransport : public QObject
{
    Q_OBJECT
public:
    explicit FgTransport(QObject *parent = 0);
    ~FgTransport();

    inline QString getString(const QString& node) const;
    inline qreal getFloat(const QString& node) const;
    inline qint32 getInt(const QString& node) const;

private:
    QUdpSocket *m_Socket;
    FgGenericProtocol *m_Protocol;

    QHostAddress m_Ip;
    quint16 m_Port;

    QStringList m_FdmData;

signals:
    void dataUpdated();

public slots:

private slots:
    void onSocketRead();
};

//
QString FgTransport::getString(const QString& node) const
{
    int paramIndex = m_Protocol->getParamIndex(node);
    if (paramIndex > -1)
    {
        return m_FdmData[paramIndex];
    }

    return "";
}

qreal FgTransport::getFloat(const QString& node) const
{
    QString param = getString(node);
    if (param.isEmpty())
    {
        return 0.0;
    }

    bool ok = false;
    qreal res = param.toFloat(&ok);
    if (!ok)
    {
        return 0.0;
    }

    return res;
}

qint32 FgTransport::getInt(const QString& node) const
{
    QString param = getString(node);
    if (param.isEmpty())
    {
        return 0.0;
    }

    bool ok = false;
    qint32 res = param.toInt(&ok);
    if (!ok)
    {
        return 0.0;
    }

    return res;
}

#endif // FGPROTOCOL_H
