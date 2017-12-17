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

import QtQuick 2.7

QtObject {
    id: controlledAircraft

    property alias qtObject: controlledAircraft
    property string callsign: __createCallsign()
    property bool connected: false

    function runFlightGear () {
        console.info("[tst_ControlledAircraft] running Flight Gear for:", callsign);
        connectedTimer.restart();
    }

    /* private declarations is not exists in C++ class */
    function __createCallsign() {
        return Date().toString();
    }
    function __randomArbitary (min, max) {
        return (Math.random() * (max - min) + min);
    }

    readonly property int __timerInterval: 5000
    property Timer connectedTimer: Timer {
        interval: __timerInterval
        repeat: false
        onTriggered: {
            console.info("[tst_ControlledAircraft]", callsign, "connected.");
            connected = true;

            disconnectedTimer.restart();
        }
    }
    property Timer disconnectedTimer: Timer {
        interval: __timerInterval
        repeat: false
        onTriggered: {
            console.info("[tst_ControlledAircraft]", callsign, "disconnected.");
            connected = false;
        }
    }
}
