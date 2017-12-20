/*
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
import QtQuick 2.0
import QtQuick.Controls 2.3

import FGear 0.1
import FGear.Components.Actions 0.1

ActionGroup {
    id: mainViewActions
    objectName: "mainViewActions"

    property alias aircraftsPageMenuAction: __aircraftsPageMenuAction
    property alias aircraftControlPageMenuAction: __aircraftControlPageMenuAction
    property alias mapPageMenuAction: __mapPageMenuAction
    property alias instrumentsPageMenuAction: __instrumentsPageMenuAction

    FgMenuAction {
        id: __aircraftsPageMenuAction
        objectName: "aircraftsPageMenuAction"
        text: "AircraftsPage"
        pageSource: "Pages/FgAircraftsPage.qml"
        checkable: true
        checked: true
    }
    FgMenuAction {
        id: __aircraftControlPageMenuAction
        objectName: "aircraftControlPageMenuAction"
        text: "AircraftControlPage"
        pageSource: "Pages/FgAircraftControlPage.qml"
        checkable: true
    }
    FgMenuAction {
        id: __mapPageMenuAction
        objectName: "mapPageMenuAction"
        text: "MapPage"
        pageSource: "Pages/FgMapPage.qml"
        checkable: true
    }
    FgMenuAction {
        id: __instrumentsPageMenuAction
        objectName: "instrumentsPageMenuAction"
        text: "Instruments"
        pageSource: "Pages/FgInstrumentsPage.qml"
        checkable: true
    }
}
