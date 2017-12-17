#!/bin/bash
[ $# -lt 2 ] && echo "Usage: $(basename $0) <app folder> <qt quick 2 imports folder>" && exit 2
[ $(uname -s) != "Darwin" ] && echo "Run this script on Mac OS X" && exit 2;

echo "Deploying Qt"

PWD_PATH="$(dirname "${BASH_SOURCE[0]}")"
BUILD_TREE="${PWD_PATH}/.."

# copy Qt Quick 2 imports
imports="Qt QtGraphicalEffects QtQml QtQuick QtQuick.2"
imports2Dir="$1/Contents/Resources/qml"

if [ -d "$2" ]; then
        echo "- Copying Qt Quick 2 imports"
        for imp in $imports
        do
            cp -R "$2"/"$imp" "$imports2Dir"/
        done
fi

#### macdeployqt

if [ ! -d "$1/Contents/Frameworks/QtCore.framework" ]; then

    echo "- Running macdeployqt ($(which macdeployqt))"

    macdeployqt "$1" \
              "-dmg" \
            || exit 1
fi
exit 0
