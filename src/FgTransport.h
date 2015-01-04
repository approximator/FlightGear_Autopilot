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

private:
    QUdpSocket *m_Socket;
    FgGenericProtocol *m_Protocol;

    QHostAddress m_Ip;
    quint16 m_Port;

signals:

public slots:

private slots:
    void onSocketRead();
};

#endif // FGPROTOCOL_H
