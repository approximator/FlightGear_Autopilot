/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Feb 10, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include <QObject>
#include <QHash>


class FgAircraft;
class FgTransport;

class FgController : public QObject
{
    Q_OBJECT
public:
    explicit FgController(QObject *parent = 0);

signals:
    void aircraftConnected (FgAircraft* aircraft);
    void aircraftDisconnected (FgAircraft* aircraft);
    void aircraftUpdateded (FgAircraft* aircraft);

public slots:
    void updateAircraft (const QString &aircraftId);

private:
    FgTransport *m_Transport;
    QHash<QString, FgAircraft*> m_OtherAircrafts;

private slots:
    void onDataReceived();
};

#endif // FGCONTROLLER_H
