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

import qbs

CppApplicationBase {
    targetName: project.appAppTarget

    Depends { name: "Qt"; submodules: [ "qml", "quick", "gui",
            "network", "xml", "svg"] }

    Depends { name: "qml_fgear" }
    Depends { name: "qml_material" }
    Depends { name: "libqtqmltricks-qtqmlmodels" }
    Depends { name: "libqtqmltricks-qtsupermacros" }

    cpp.includePaths: [".", "utils"]

    /* Main source file */
    Group {
        name: "Sources"
        files: [
            "../main.cpp",
            "*.cpp",
            "autopilot/*.cpp",
            "flightgear/*.cpp",
            "utils/*.cpp",
            "vehicle/*.cpp"
        ]
    }

    Group {
        name: "Headers"
        files: [
            "*.h",
            "autopilot/*.h",
            "flightgear/*.h",
            "utils/*.h",
            "vehicle/*.h"
        ]
    }

    Group {
        name: "Resources"
        files: "../resources/qml/qml_res.qrc"
    }

    /* Fgap JSON configs */
    Group {
        name: "jsonConfigs"
        fileTags: ["jsonConfigs"]
        prefix: project.appConfigSourceRoot
        files: "*"
    }

    targetInstallDir: project.appInstallDir
    targetInstallPrefix: project.appBinDir
}
