#!/bin/bash

COMMAND=$1
SCREENSHOT_FILE=$2

# run Xvfb
Xvfb :5 -screen 0 1280x1024x24 -fbdir /tmp &
XVFB_PID=$!
sleep 2

# run command
DISPLAY=:5 "$COMMAND" &
COMMAND_PID=$!
# wait
sleep 20

# take screenshot
DISPLAY=:5 import -window root "${SCREENSHOT_FILE}"

# kill everything
sleep 2
kill -15 $COMMAND_PID
sleep 2
kill -15 $XVFB_PID
sleep 2
