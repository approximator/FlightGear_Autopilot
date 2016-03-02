/*!
 * @file FgAircraftsManager.h
 *
 * @brief Aircrafts model
 *
 *
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 * Author: Andrii Shelest
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FGCONTROLLER_H
#define FGCONTROLLER_H

#include "QQmlObjectListModel.h"
#include "QQmlVarPropertyHelpers.h"
#include "vehicle/FgControlledAircraft.h"

#include <QAbstractListModel>
#include <QList>

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
    FgTransport *m_Transport{ nullptr };
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
