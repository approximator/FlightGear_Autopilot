/*!
 * @file FgAircraftsModel.h
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jul 20, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "FgAircraft.h" //DO NOT REMOVE THIS (needed for transferring types in signals)!!!
#include "FgControlledAircraft.h"

#include <QAbstractListModel>
#include <QList>

class FgTransport;

class FgAircraftsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FgAircraftsModel(QObject *parent = 0);
    virtual ~FgAircraftsModel();
    bool init();
    bool saveConfig(const QString& filename);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
    std::shared_ptr<FgTransport>                 m_Transport { };
    QList<std::shared_ptr<FgControlledAircraft>> m_OurAircrafts { };
    QList<std::shared_ptr<FgAircraft>>           m_OtherAircrafts { };
    qint32 m_AircraftsCount { 0 };

    void updateOurAircraftsCount();
    void updateOtherAircraftsCount();

private slots:
    void onDataReceived();
    void onAircraftConnected();

public slots:
    void updateAircraft(const QString &aircraftId);

signals:
    void aircraftAdded(FgAircraft* aircraft);
    void ourAircraftAdded(FgAircraft* aircraft);
    void aircraftConnected(FgAircraft* aircraft);
    void aircraftDisconnected(FgAircraft* aircraft);
    void aircraftUpdated(FgAircraft* aircraft);

    void fdmDataChanged(std::shared_ptr<FgTransport> transport);
};

#endif // FGCONTROLLER_H
