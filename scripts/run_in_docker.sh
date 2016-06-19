#!/bin/bash

SRC_DIR=$(cd $(dirname $0)/../ && pwd)
SCRIPT_NAME="$(basename \"$(test -L \"$0\" && readlink \"$0\" || echo \"$0\")\")"
ENTRY_POINT="/tmp/dock_fgap_run_entry_point.sh"

: ${INSTALL_DIR:="/tmp/fgap/docker"}
echo "INSTALL_DIR: ${INSTALL_DIR}"

cat > ${ENTRY_POINT} << EOF
#!/bin/bash
groupadd -g $(getent group $USER | cut -d: -f3) $USER
useradd -m -g $USER -G sudo -N -u $UID $USER
chown -R $USER:$USER /fgap
/bin/su $USER -c "/fgap/install/FlightGear_Autopilot/fgautopilot"

EOF
chmod +x ${ENTRY_POINT}

VOLUMES="-v ${ENTRY_POINT}:${ENTRY_POINT}:ro"
VOLUMES="${VOLUMES} -v /tmp/.X11-unix:/tmp/.X11-unix -v /dev/shm:/dev/shm"
VOLUMES="${VOLUMES} -v ${INSTALL_DIR}:/fgap"

docker run --rm --entrypoint=${ENTRY_POINT} ${VOLUMES} -e DISPLAY=$DISPLAY  approximator/qttest
rm ${ENTRY_POINT}
