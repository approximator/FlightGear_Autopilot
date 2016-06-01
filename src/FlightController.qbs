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
import qbs.FileInfo
import QmlTools

QmlTools.QtQmlApplication
{
    name: "FlightGear_Autopilot"
    appShortName: "fgautopilot"

    Depends { name: "Qt"; submodules: [
            "qml", "quick",
            "network", "xml", "svg"
        ] }

    Depends { name: "libqtqmltricks-qtqmlmodels" }
    Depends { name: "libqtqmltricks-qtsupermacros" }

    cpp.includePaths: ["FlightController/", "FlightController/utils"]
    cpp.defines: generalDefines.concat(['QTQMLTRICKS_NO_PREFIX_ON_GETTERS'])

    qmlImportsPaths: [
        FileInfo.joinPaths(project.appSourceRoot, "contrib", "qml-material", "modules"),
        FileInfo.joinPaths(sourceDirectory, "Gui", "qml", "qml-fgear", "modules")
    ]

    /* Main source file */
    Group {
        name: "main_source"
        files: [
            "main.cpp",
        ]
    }

    Group {
        name: "Sources"
        prefix: "FlightController/**/"
        files: [
            "*.cpp"
        ]
    }

    Group {
        name: "Headers"
        prefix: "FlightController/**/"
        files: [
            "*.h"
        ]
    }

    Group {
        name: "Resources"
        files: "resources/qml/qml_res.qrc"
    }

    /* Fgap JSON configs */
    Group {
        name: "jsonConfigs"
        fileTags: ["jsonConfigs"]
        prefix: appConfigSourceRoot
        files: "*"
    }
}
