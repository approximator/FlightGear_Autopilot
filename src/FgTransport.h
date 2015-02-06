/*!
 * @file FgTransport.h
 *
 * @brief Transport for interacting with FlightGear
 *
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Jan 04, 2015
 * @date Modified Jan 06, 2015
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
    inline void setExists(bool *exists, bool value) const;

    inline FgGenericProtocol* protocol() const;

private:
    QUdpSocket *m_Socket;
    FgGenericProtocol *m_Protocol;

    QHostAddress m_Ip;
    quint16 m_Port;

    QStringList m_FdmData;

signals:
    void fgDataReceived(const QString &data);

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
        setExists(exists, true);
        return m_FdmData[paramIndex]; //! @todo check index
    }

    setExists(exists, false);
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

void FgTransport::setExists(bool *exists, bool value) const
{
    if (exists)
    {
        *exists = value;
    }
}

FgGenericProtocol *FgTransport::protocol() const
{
    return m_Protocol;
}

#endif // FGPROTOCOL_H
