#!/bin/bash

if [ $# != 3 ]; then
   echo "Error! Please provide 3 parameters"
   echo "FGAP_SRC_DIR, FGAP_INSTALL_DIR, BUILD_VARIANT"
   exit 1
fi

ROOT_DIR=$(cd $(dirname $0) && pwd)
DEPLOY_SCRIPT=$(cd ${ROOT_DIR}/../contrib/Qt-Qbs-Application/scripts && pwd)/deployqt.py
FGAP_SRC_DIR=$1
FGAP_INSTALL_DIR=$2
BUILD_VARIANT=$3     # release or debug

# [ ! -z "$QTDIR" ] && export PATH=$QTDIR/bin:$PATH

echo ""
echo "I am: $(id)"
echo ""
echo "FGAP_SRC_DIR: $FGAP_SRC_DIR"
echo "FGAP_INSTALL_DIR: $FGAP_INSTALL_DIR"
echo "BUILD_VARIANT: $BUILD_VARIANT"

qbs setup-toolchains --detect
qbs setup-qt $(which qmake) qt
qbs config profiles.qt.baseProfile gcc
qbs config --list profiles
qbs config defaultProfile qt

qbs build                                \
    --file $FGAP_SRC_DIR                 \
    --command-echo-mode command-line     \
    --clean-install-root                 \
    --build-directory /tmp/fgap_build    \
    $BUILD_VARIANT                       \
    qbs.installRoot:$FGAP_INSTALL_DIR    \
    profile:qt

if [ $? -ne 0 ]; then
    echo "qbs build failed"
    exit 1
fi

python -u ${DEPLOY_SCRIPT}                                                     \
          --app-file      $FGAP_INSTALL_DIR/FlightGear_Autopilot/fgautopilot   \
          --install-dir   $FGAP_INSTALL_DIR/FlightGear_Autopilot               \
          --data-dir      $FGAP_INSTALL_DIR/FlightGear_Autopilot/data          \
          --libraries-dir $FGAP_INSTALL_DIR/FlightGear_Autopilot/data/lib      \
          --qmake         $(which qmake)                                       \
          --debug-build   $BUILD_VARIANT                                       \
          --libs          Qt5Core Qt5Widgets Qt5Gui Qt5Qml Qt5Quick Qt5Network \
                          Qt5DBus Qt5Svg Qt5XcbQpa icudata icui18n icuuc pcre  \
          --qt-plugins    iconengines imageformats platforms                   \
                          platforminputcontexts xcbglintegrations              \
          --qml           Qt QtQuick QtQuick.2 QtGraphicalEffects

if [ $? -ne 0 ]; then
    echo "Deploy failed"
    exit 1
fi
