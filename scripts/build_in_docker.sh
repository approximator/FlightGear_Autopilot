#!/bin/bash

if [ $# = 1 ]; then
   QBS_VERSION=$1
fi

SRC_DIR=$(cd $(dirname $0)/../ && pwd)
SCRIPT_NAME="$(basename \"$(test -L \"$0\" && readlink \"$0\" || echo \"$0\")\")"
ENTRY_POINT="/tmp/dock_fgap_entry_point.sh"

: ${FGAP_SRC_DIR:=$(cd "${SRC_DIR}/.." && pwd)}
: ${INSTALL_DIR:="/tmp/fgap/docker"}
: ${BUILD_VARIANT:="release"}
: ${QBS_VERSION:="qbs:1.5.0.Qt5.6.1"}

echo "SRC_DIR: ${FGAP_SRC_DIR}"
echo "INSTALL_DIR: ${INSTALL_DIR}"
echo "BUILD_VARIANT: ${BUILD_VARIANT}"
echo "QBS_VERSION: ${QBS_VERSION}"

mkdir -p ${INSTALL_DIR}

cat > ${ENTRY_POINT} << EOF
#!/bin/bash
groupadd -g $(getent group $USER | cut -d: -f3) $USER
useradd -m -g $USER -G sudo -N -u $UID $USER
chown -R $USER:$USER /fgap
/bin/su $USER -c "cd /home/prj/fgap && ./scripts/build.sh /home/prj/fgap /fgap/install ${BUILD_VARIANT}"

EOF
chmod +x ${ENTRY_POINT}

VOLUMES="-v ${ENTRY_POINT}:${ENTRY_POINT}:ro -v ${SRC_DIR}:/home/prj/fgap:ro"
VOLUMES="${VOLUMES} -v ${INSTALL_DIR}:/fgap"

docker run --rm --entrypoint=${ENTRY_POINT} ${VOLUMES} approximator/${QBS_VERSION}
rm ${ENTRY_POINT}

echo "Build finished!"
echo "fgap installed in: ${INSTALL_DIR}"
