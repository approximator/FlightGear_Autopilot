#!/bin/bash

THIS_DIR=$(cd $(dirname $0) && pwd)

export APP_DIR_NAME=FlightGear_Autopilot    # install here
export APP_NAME=fgautopilot
export SRC_DIR=$(cd "$THIS_DIR"/../FlightControlCenter && pwd)
export INSTALL_DIR=/tmp/fgap/docker
export SCRIPTS_DIR="$SRC_DIR/submodules/qt-qbs-application/scripts"
export DEPLOYMENT_INFO_FILE="$SRC_DIR/deployment_info"

"$SCRIPTS_DIR/build_in_docker.sh"
