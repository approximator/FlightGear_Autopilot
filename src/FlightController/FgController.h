/*!
 * @file FgController.cpp
 *
 * @brief Controller
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jun 30, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "FgAircraft.h" //DO NOT REMOVE THIS (needed for transferring types in signals)!!!
#include "FgControlledAircraft.h"

#include <QObject>
#include <QHash>

class FgTransport;

class FgController : public QObject
{
    Q_OBJECT
public:
    explicit FgController(QObject *parent = 0);
    virtual ~FgController();
    bool init();

private:
    std::shared_ptr<FgTransport> m_Transport { };
    QHash<QString, std::shared_ptr<FgControlledAircraft>> m_OurAircrafts { };
    QHash<QString, std::shared_ptr<FgAircraft>> m_OtherAircrafts { };
    qint32 m_AircraftsCount { 0 };

    void updateOurAircraftsCount();
    void updateOtherAircraftsCount();

private slots:
    void onDataReceived();

public slots:
    void updateAircraft(const QString &aircraftId);

signals:
    void aircraftConnected(FgAircraft* aircraft);
    void ourAircraftConnected(FgAircraft* aircraft);
    void aircraftDisconnected(FgAircraft* aircraft);
    void aircraftUpdated(FgAircraft* aircraft);

    void fdmDataChanged(std::shared_ptr<FgTransport> transport);
};

#endif // FGCONTROLLER_H
