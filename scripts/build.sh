#!/bin/bash

if [ $# != 3 ]; then
   echo "Error! Please provide 3 parameters"
   echo "FGAP_SRC_DIR, FGAP_INSTALL_DIR, BUILD_VARIANT"
   exit 1
fi

ROOT_DIR=$(cd $(dirname $0) && pwd)
FGAP_SRC_DIR=$1
FGAP_INSTALL_DIR=$2
BUILD_VARIANT=$3     # release or debug

qbs setup-toolchains --detect
qbs setup-qt --detect
qbs setup-qt $(which qmake) qt
qbs config defaultProfile qt

cd $FGAP_SRC_DIR/src

qbs --command-echo-mode command-line \
    -d /tmp/fgap_build/              \
    --clean-install-root qbs.installRoot:$FGAP_INSTALL_DIR

python -u $FGAP_SRC_DIR/scripts/deployqt.py                  \
          $FGAP_INSTALL_DIR/FlightGear_Autopilot/fgautopilot \
          $FGAP_INSTALL_DIR/FlightGear_Autopilot             \
          $FGAP_INSTALL_DIR/FlightGear_Autopilot/data        \
          $FGAP_INSTALL_DIR/FlightGear_Autopilot/data/lib    \
          $(which qmake) \
          $BUILD_VARIANT
