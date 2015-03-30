#!/bin/bash
[ $# -lt 5 ] && echo "Usage: $(basename $0) <app folder> <qt translations folder> <qt plugin folder> <qt quick imports folder> <qt quick 2 imports folder>" && exit 2
[ $(uname -s) != "Darwin" ] && echo "Run this script on Mac OS X" && exit 2;

echo "Deploying Qt"

PWD_PATH="$(dirname "${BASH_SOURCE[0]}")"
BUILD_TREE="${PWD_PATH}/.."
ModVersion=0.0.5

# copy Qt Quick 2 imports
imports2Dir="$1/Contents/Imports/qtquick2"
if [ -d "$5" ]; then
    if [ ! -d "$imports2Dir" ]; then
        echo "- Copying Qt Quick 2 imports"
        mkdir -p "$imports2Dir"
        cp -R "$5"/ "$imports2Dir"/

        echo "- Downloading additional Qt Quick 2 imports"
        "${PWD_PATH}/load_qml_module.sh" qml-extras "${BUILD_TREE}/qml-libs" "https://github.com/papyros/qml-extras/archive/v${ModVersion}.zip"
        "${PWD_PATH}/load_qml_module.sh" qml-material "${BUILD_TREE}/qml-libs" "https://github.com/papyros/qml-material/archive/v${ModVersion}.zip"
        "${PWD_PATH}/load_qml_module.sh" qml-fgear "${BUILD_TREE}/qml-libs"

        echo "- Copying additional Qt Quick 2 imports"
        cp -R "${BUILD_TREE}/qml-libs/qml-fgear/modules/FGear" "$imports2Dir"/
        cp -R "${BUILD_TREE}/qml-libs/qml-material/modules/Material" "$imports2Dir"/
        cp -R "${BUILD_TREE}/qml-libs/qml-extras/modules/Material" "$imports2Dir"/
    fi
fi

# copy qt creator qt.conf
if [ ! -f "$1/Contents/Resources/qt.conf" ]; then
    echo "- Copying qt.conf"
    cp -f "${BUILD_TREE}/dist/installer/mac/qt.conf" "$1/Contents/Resources/qt.conf" || exit 1
fi

#### macdeployqt

if [ ! -d "$1/Contents/Frameworks/QtCore.framework" ]; then

    echo "- Running macdeployqt ($(which macdeployqt))"

    macdeployqt "$1" "-dmg"  || exit 1
#        "-executable=$1/Contents/Resources/qtpromaker" \
fi
