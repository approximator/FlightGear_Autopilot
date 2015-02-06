#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include <QObject>
#include <QHash>
#include "FgAircraft.h" //Needed for signals type

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
    QHash<QString, FgAircraft*> m_Aircrafts;

private slots:
    void parseFgData (const QString &data);
};

#endif // FGCONTROLLER_H
