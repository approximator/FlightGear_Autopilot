/*!
 * @file FgAircraftsManager.h
 *
 * @brief Aircrafts model
 *
 * @author Andrey Shelest
 * @author Oleksii Aliakin (alex@nls.la)
 * @date Created Feb 08, 2015
 * @date Modified Jan 24, 2016
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"
#include "vehicle/FgControlledAircraft.h"

#include <QList>
#include <QAbstractListModel>

class FgTransport;
typedef QQmlObjectListModel<FgControlledAircraft> TAirModel;

class FgAircraftsManager : public QObject
{
    Q_OBJECT
    QML_READONLY_VAR_PROPERTY(TAirModel *, model)

public:
    explicit FgAircraftsManager(QObject *parent = 0);
    virtual ~FgAircraftsManager();
    bool init();
    bool saveConfig();

    Q_INVOKABLE bool addAircraft();
    Q_INVOKABLE bool addAircraft(QSettings &settings);

private:
    FgTransport *m_Transport{nullptr};
    std::tuple<int, int> getAvailablePorts() const;

    FgAircraftsManager(const FgAircraftsManager &other);
    FgAircraftsManager &operator=(const FgAircraftsManager &other);

private slots:
    void onDataReceived(FgTransport *transport);
    void onAircraftConnected();

signals:
    void fdmDataChanged(FgTransport *transport);
};

#endif /* FGCONTROLLER_H */
