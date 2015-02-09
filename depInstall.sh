#!/bin/bash

THIS_DIR=$(cd $(dirname $0) && pwd)

echo $THIS_DIR

git clone https://github.com/papyros/qml-material $THIS_DIR/mat
git clone https://github.com/papyros/qml-extras $THIS_DIR/extras

cd $THIS_DIR/mat
pwd
echo "Make qml-material"
ls -lah
qmake -v && qmake && make && sudo make install

cd $THIS_DIR/extras 
pwd
echo "Make qml-extras"
ls -lah
qmake -v && qmake && make && sudo make install
