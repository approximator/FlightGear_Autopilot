#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $(basename $0) <module_source_path> <install_path>"
    exit 1
fi

BUILD_TREE="$(dirname "${BASH_SOURCE[0]}")/.."
SOURCES_PATH="$1"
INSTALL_PATH="$2"

WGET_PATH=`which wget`
if [ ! -e "$WGET_PATH" ]; then
    WGET_PATH="/usr/local/bin/wget"
fi

MODULES_VERSION="0.0.5"

cd $SOURCES_PATH

download_and_deploy(){
    src_dir_name=$1
    module_name=$2
    url=$3

    if [ -d "$INSTALL_PATH/$module_name" ]; then
        echo "Module $module_name already deployed in $INSTALL_PATH"
        return 0
    fi

    if [ -d "$SOURCES_PATH/$src_dir_name" ]; then
        echo "Module $module_name already loaded"
    else
        if [ ! -e "$url" ]; then
            echo "Downloading module from:$url"
            $WGET_PATH $url -O $src_dir_name.zip

            echo "Extracting module from:$src_dir_name..."
            unzip $src_dir_name.zip
            module_dir_name=`find . -type d -name "$src_dir_name*"`
            echo "Rename downloaded dir III $module_dir_name II to $src_dir_name"
            mv $module_dir_name $src_dir_name

            echo "Removing module archive..."
            rm -rf $src_dir_name.zip
            echo "Module $src_dir_name downloaded successfully."
        else
              echo "Error: can not load or find module dir"
              exit -1
        fi

    fi

    echo "Deploy module $src_dir_name into bundle"
    dest_path="$INSTALL_PATH/$module_name"
    if [ ! -d "$dest_path" ]; then
        mkdir -p "$dest_path"
    fi
    cp -R "$SOURCES_PATH/$src_dir_name/modules/$module_name/"* "$dest_path/"

}

download_and_deploy "qml-material" "Material" "https://github.com/papyros/qml-material/archive/v${MODULES_VERSION}.zip"
download_and_deploy "qml-extras" "Material/Extras" "https://github.com/papyros/qml-extras/archive/v${MODULES_VERSION}.zip"
download_and_deploy "qml-fgear" "FGear"

exit 0
