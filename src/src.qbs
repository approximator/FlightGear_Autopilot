/*
 * Copyright © 2015-2017 Andrii Shelest. All rights reserved.
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

import qbs
import qbs.FileInfo

Project {
    name: "app_sources"

    QtQmlApplication {
        name: "FlightGear_Autopilot"

        Depends { name: "app_config" }
        Depends { name: "flight_controller" }

        /* Main source file */
        Group {
            name: "main_source"
            files: [ "main.cpp" ]
        }

        Group {
            name: "main_resources"
            files: "resources/qml/qml_res.qrc"
        }
    }

    references: [
        "FlightController/FlightController.qbs",
        "Gui/qml/qml.qbs"
    ]
}
