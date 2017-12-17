#!/bin/bash

ROOT_DIR=$(cd $(dirname $0)/../ && pwd)

VOLUMES="-v $ROOT_DIR:/src"

docker run --rm -ti ${VOLUMES} --workdir=/src -e HOST_USER_ID=$(id -u) -e HOST_USER_GROUP_ID=$(id -g) -e HOST_USER_NAME=$USER approximator/clangformat:4.0 find src \( -name '*.cpp' -o -name '*.h' \) -exec clang-format-4.0 -style=file -i {} \;
