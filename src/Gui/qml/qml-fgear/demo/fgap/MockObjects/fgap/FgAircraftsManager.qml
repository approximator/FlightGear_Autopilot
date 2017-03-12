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

QtObject {
    id: aircraftsManager
    objectName: "tst_aircraftsManager"

    property list<QtObject> model

    property Component __aircraftcomponent: Component {
        FgControlledAircraft { }
    }

    /* Private functionality is not available in C++ model */
    property int __count: !!model ? model.length : 0
    property int __activeIndex: 0

    function addAircraft(callsign) {
        var initArgs = { };
        if (callsign !== "")
            initArgs["callsign"] = callsign;

        /* copy existing objects into new model */
        var modelArray = []; var i;
        for (i = 0; i < __count; i++) {
            modelArray.push(model[i]);
        }

        var newObj = __aircraftcomponent.createObject(this, initArgs);
        modelArray.push(newObj);
        model = modelArray;
        __activeIndex = model.length-1;
        console.log("[tst_AircraftsManager] aircraft added: ", newObj.callsign);
    }
}
