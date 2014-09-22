#!/bin/bash

clear && dmesg -C

if [ -z "$1" ]; then
  MORSE_CODE="- . ... - .. -. --.|... - .-. .. -. --."
else
  MORSE_CODE=$1
fi

if [ -f /proc/morse2txt ]; then
  echo >&1 '
*********************************
**       Unloading module      **
*********************************
'
  rmmod morse_module
  dmesg
fi

abort()
{
  echo >&2 '
*********************************
**   Make failed! Exiting...   **
*********************************
'
  exit 1
}
trap 'abort' 0
set -e

echo >&1 '
*********************************
**        Running Make         **
*********************************
'
make clean && make
trap : 0

if [ -f morse_module.ko ]; then
  echo >&1 '
*********************************
**        Loading module       **
*********************************
'
  insmod morse_module.ko
  dmesg
fi

echo >&1 '
*********************************
**      Writing to procfs      **
*********************************
'
echo "\$ echo "$MORSE_CODE" > /proc/morse2txt
"
echo $MORSE_CODE > /proc/morse2txt
dmesg

echo >&1 '
*********************************
**     Reading from procfs     **
*********************************

$ cat /proc/morse2txt
'
cat /proc/morse2txt
echo " "

