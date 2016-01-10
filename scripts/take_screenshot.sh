#!/bin/bash

COMMAND=$1
SCREENSHOT_FILE=$2

echo "Command = $COMMAND"

Xvfb :5 -screen 0 1280x1024x24 &
XVFB_PID=$!

sleep 2
# run command
DISPLAY=:5 $COMMAND &
COMMAND_PID=$!
# wait
sleep 60

# take screenshot
DISPLAY=:5 import -window root "${SCREENSHOT_FILE}"

sleep 2
kill -15 $COMMAND_PID
sleep 2
kill -15 $XVFB_PID
