#!/bin/bash

clear && dmesg -C

if [ -z "$1" ]; then
  MORSE_CODE="- . ... - .. -. --.|... - .-. .. -. --."
else
  MORSE_CODE=$1
fi

if [ -f /proc/morse ]; then
  echo " "
  echo "****************************"
  echo "**  rmmod morse_module    **"
  echo "****************************"
  echo " "
  rmmod morse_module
  dmesg
fi

abort()
{
  echo >&2 '
  *****************************
  ** Make failed. Exiting... **"
  *****************************'
  exit 1
}
trap 'abort' 0
set -e
make clean && make
trap : 0

if [ -f morse_module.ko ]; then
  echo " "
  echo "****************************"
  echo "** insmod morse_module.ko **"
  echo "****************************"
  echo " "
  insmod morse_module.ko
  dmesg
  echo " "
fi

echo "***********************"
echo "** writing to procfs **"
echo "***********************"
echo " "
echo "\$ echo \"$MORSE_CODE\" > /proc/morse"
echo $MORSE_CODE > /proc/morse
echo " "
dmesg

echo " "
echo "*************************"
echo "** reading from procfs **"
echo "*************************"
echo " "
echo "\$ cat /proc/morse"
echo " "
cat /proc/morse
echo " "

