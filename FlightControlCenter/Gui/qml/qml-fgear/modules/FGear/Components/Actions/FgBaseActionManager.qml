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

import FGear 0.1
import FGear.Components.Actions 0.1

QtObject {
    id: baseActionManager
    objectName: "baseActionManager"

    property list<FgBaseAction> actions

    function getByName(name) {
        var i = 0;
        var result = null;
        for (; i < actions.length; i++) {
            if (actions[i].objectName === name) {
                result = actions[i];
                break;
            }
        }

        return result;
    }

    function getActionsByName(nameSufix) {
        var i = 0;
        var foundActions = [];
        for (; i < actions.length; i++) {
            if (actions[i].objectName.search(nameSufix) !== -1 ) {
                foundActions.push(actions[i]);
            }
        }
        return foundActions;
    }

    Component.onCompleted: {
        var i = 0;
        for (; i < actions.length; i++)
            console.info("[ActionManager] Registered action: ", actions[i].objectName)
    }
}
