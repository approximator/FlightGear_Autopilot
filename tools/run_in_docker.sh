#!/bin/bash

SRC_DIR=$(cd $(dirname $0)/../ && pwd)
SCRIPT_NAME="$(basename \"$(test -L \"$0\" && readlink \"$0\" || echo \"$0\")\")"
ENTRY_POINT="/tmp/dock_fgap_run_entry_point.sh"

: ${INSTALL_DIR:="/tmp/fgap"}
echo "INSTALL_DIR: ${INSTALL_DIR}"

cat > ${ENTRY_POINT} << EOF
#!/bin/bash
if [ ! -d /home/$USER ]; then
    mkdir -p /home/$USER
fi

grep $(id -g) /etc/group >> /dev/null
[[ $? -eq 0 ]] || groupadd -g $(id -g) $USER

useradd -N -u $(id -u) $USER
chown $(id -u):$(id -g) /home/$USER

export HOME=/home/$USER
export USER=$USER

/bin/su $USER -c "/fgap/fgautopilot"

EOF
chmod +x ${ENTRY_POINT}

docker run --rm                         \
    --entrypoint=${ENTRY_POINT}         \
    -v ${ENTRY_POINT}:${ENTRY_POINT}:ro \
    -v /tmp/.X11-unix:/tmp/.X11-unix    \
    -v /dev/shm:/dev/shm                \
    -v ${INSTALL_DIR}:/fgap             \
    -e DISPLAY=$DISPLAY                 \
    approximator/qttest

rm ${ENTRY_POINT}
