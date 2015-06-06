#!/bin/bash

PROJ_NAME=$1
COMMIT_MSG=$2
FILE=$3
DISP_NAME=$4

echo "Uploading file: ${FILE} (${DISP_NAME})"
echo "       Project: ${PROJ_NAME}"
echo "        Commit: ${COMMIT_MSG}"

echo "Artiuser ${ARTI_USER}"

if [ ! -f "${FILE}" ]; then
    echo "Can not upload file. File does not exist."
    exit 1
fi

rm -f /tmp/travis.json
rm -f /tmp/http.log
http -v --session=/tmp/travis.json GET https://arti.nls.la/accounts/login/ next==/projects/file/upload/ >> /tmp/http.log
tok=$(grep "csrftoken=" /tmp/http.log | tail -n1) ; tok=${tok#*=} ; tok=${tok%%;*} #; rm /tmp/http.log
http -v --session=/tmp/travis.json -f POST https://arti.nls.la/accounts/login/ csrfmiddlewaretoken=${tok} username="$ARTI_USER" password="$ARTI_PASS" >> /tmp/http.log
tok=$(grep "csrftoken=" /tmp/http.log | tail -n1) ; tok=${tok#*=} ; tok=${tok%%;*} #; rm /tmp/http.log
http -v --session=/tmp/travis.json -f POST https://arti.nls.la/projects/file/upload/ csrfmiddlewaretoken=${tok} display_name="${DISP_NAME}" file@"${FILE}" project_name="${PROJ_NAME}" build_commit_msg="${COMMIT_MSG}" >> /tmp/http.log
