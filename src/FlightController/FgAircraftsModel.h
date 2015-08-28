/*!
 * @file FgAircraftsModel.h
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Aug 28, 2015
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "FgControlledAircraft.h"

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
    std::shared_ptr<FgTransport>                 m_Transport { };
    QList<std::shared_ptr<FgControlledAircraft>> m_OurAircrafts { };
    qint32 m_AircraftsCount { 0    };

    QHash<int, QByteArray> m_Roles {
        { Roles::Name     , "name"     },
        { Roles::Connected, "connected"},
        { Roles::Aircraft , "aircraft" }
    };

    std::tuple<int, int> getAvailablePorts() const;

private slots:
    void onDataReceived();
    void onAircraftConnected();

signals:
    void aircraftAdded(FgAircraft* aircraft);
    void ourAircraftAdded(FgAircraft* aircraft);
    void aircraftConnected(FgAircraft* aircraft);
    void aircraftDisconnected(FgAircraft* aircraft);
    void aircraftUpdated(FgAircraft* aircraft);

    void fdmDataChanged(std::shared_ptr<FgTransport> transport);
};

#endif // FGCONTROLLER_H
