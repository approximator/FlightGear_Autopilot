#!/bin/bash

COMMAND=$1
SCREENSHOT_FILE=$2

echo "Command = $COMMAND"
sleep 2
# run command
$COMMAND &
COMMAND_PID=$!
# wait
sleep 30

# take screenshot
import -window root "${SCREENSHOT_FILE}"

sleep 2
kill -15 $COMMAND_PID
sleep 2
