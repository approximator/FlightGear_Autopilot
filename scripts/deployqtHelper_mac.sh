#!/bin/bash
[ $# -lt 5 ] && echo "Usage: $(basename $0) <app folder> <qt translations folder> <qt plugin folder> <qt quick imports folder> <qt quick 2 imports folder>" && exit 2
[ $(uname -s) != "Darwin" ] && echo "Run this script on Mac OS X" && exit 2;

echo "Deploying Qt"

PWD_PATH="$(dirname "${BASH_SOURCE[0]}")"
BUILD_TREE="${PWD_PATH}/.."
ModVersion=0.0.5

# copy Qt Quick 2 imports
imports2Dir="$1/Contents/Resources/qml"
if [ -d "$5" ]; then
    if [ ! -d "$imports2Dir" ]; then
        echo "- Copying Qt Quick 2 imports"
        mkdir -p "$imports2Dir"
        cp -R "$5"/ "$imports2Dir"/
    fi
fi

#### macdeployqt

if [ ! -d "$1/Contents/Frameworks/QtCore.framework" ]; then

    echo "- Running macdeployqt ($(which macdeployqt))"

    macdeployqt "$1" "-dmg"  || exit 1
#        "-executable=$1/Contents/Resources/qtpromaker" \
fi
