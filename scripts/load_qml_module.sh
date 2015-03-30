#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $(basename $0) <module_name> <install_path> <module_url>"
    exit 1
fi

BUILD_TREE="$(dirname "${BASH_SOURCE[0]}")/.."
MODULE_NAME="$1"
INSTALL_PATH="$2"
DOWNLOAD_URL="$3"

cd $INSTALL_PATH
if [ -d "$MODULE_NAME" ]; then
    echo "Module $MODULE_NAME already loaded"
else
    if [ ! -e "$DOWNLOAD_URL" ]; then
        echo "Downloading module from:$DOWNLOAD_URL"
        /usr/local/bin/wget $DOWNLOAD_URL -O $MODULE_NAME.zip

        echo "Extracting module from:$MODULE_NAME..."
        unzip $MODULE_NAME.zip
        MODULE_DIR_NAME=`find . -type d -name "$MODULE_NAME*"`
        echo "Rename downloaded dir III $MODULE_DIR_NAME II to $MODULE_NAME"
        mv $MODULE_DIR_NAME $MODULE_NAME

        echo "Removing module archive..."
        rm -rf $MODULE_NAME.zip
        echo "Module $MODULE_NAME downloaded successfully."
    else
          echo "Error: can not load or find module dir"
          exit -1
    fi
fi

#   MODULE_DIR_NAME=`find . -type d -name $MODULE_NAME/modules`
#if [ ! -e "INSTALL_DIR" ]; then
#    echo "Deploy module $MODULE_DIR_NAME into bundle"
#    cp -R $MODULE_NAME/modules/$MODULE_DIR_NAME $INSTALL_DIR
#else
#    echo "Error: $MODULE_NAME Deploy failed!!!"
#    exit -2
#fi
exit 0
