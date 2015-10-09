/*!
 * @file FgAircraftsModel.h
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Oct 05, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "vehicle/FgControlledAircraft.h"

#include <QList>
#include <QAbstractListModel>

class FgTransport;

class FgAircraftsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Name = Qt::UserRole + 1,
        Connected,
        Aircraft
    };

    explicit FgAircraftsModel(QObject *parent = 0);
    virtual ~FgAircraftsModel();
    bool init();
    bool saveConfig();

    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

    Q_INVOKABLE FgControlledAircraft* get(int index) const;
    Q_INVOKABLE void runFlightgear(int index) const;

    Q_INVOKABLE bool addAircraft();
    Q_INVOKABLE bool addAircraft(QSettings &settings);

protected:
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    FgTransport* m_Transport { nullptr };
    QList<std::shared_ptr<FgControlledAircraft>> m_OurAircrafts { };
    qint32 m_AircraftsCount { 0    };

    QHash<int, QByteArray> m_Roles {};

    std::tuple<int, int> getAvailablePorts() const;

    FgAircraftsModel(const FgAircraftsModel& other);
    FgAircraftsModel& operator=(const FgAircraftsModel& other);

private slots:
    void onDataReceived(FgTransport *transport);
    void onAircraftConnected();

signals:
    void aircraftAdded(FgAircraft* aircraft);
    void ourAircraftAdded(FgAircraft* aircraft);
    void aircraftConnected(FgAircraft* aircraft);
    void aircraftDisconnected(FgAircraft* aircraft);
    void aircraftUpdated(FgAircraft* aircraft);

    void fdmDataChanged(FgTransport* transport);
};

#endif // FGCONTROLLER_H
