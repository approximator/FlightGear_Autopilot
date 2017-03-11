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
import QtQml.Models 2.2

import "fgObjects.js" as Tools

QtObject {
    id: aircraftsManager

    readonly property ListModel model: ListModel { }

    /* Private functionality is not available in C++ model */
    property int __activeIndex: -1
    readonly property var __activeElement: model.get(__activeIndex)

    function addAircraft(callsign) {
        var initArgs = new Tools.Aircraft(callsign);

        model.append(initArgs);
        __activeIndex = model.count-1;
        console.log("[tst_AircraftsManager] aircraft added: ", __activeElement.callsign);

        connectedTimer.restart();
    }

    readonly property int __timerInterval: 5000
    property Timer connectedTimer: Timer {
        interval: __timerInterval
        repeat: false
        onTriggered: {
            console.log("[tst_AircraftsManager] aircraft connected:",
                        __activeElement.callsign);
            model.setProperty(__activeIndex, "connected", true);

            disconnectedTimer.restart();
        }
    }
    property Timer disconnectedTimer: Timer {
        interval: __timerInterval
        repeat: false
        onTriggered: {
            console.log("[tst_AircraftsManager] aircraft disconnected:",
                        __activeElement.callsign);
            model.setProperty(__activeIndex, "connected", false);
        }
    }
}
