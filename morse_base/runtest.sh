#!/bin/bash

MORSE_CODE="- . ... - .. -. --.|... - .-. .. -. --."

if [ -f /proc/morse ]; then
  rmmod morse_module
  dmesg
fi

dmesg -C
make clean && make && clear

if [ -f morse_module.ko ]; then
  echo "****************************"
  echo "** insmod morse_module.ko **"
  echo "****************************"
  echo " "
  insmod morse_module.ko
  dmesg
  echo " "
  dmesg -C
fi

echo "***********************"
echo "** writing to procfs **"
echo "***********************"
echo " "
echo "morse: $MORSE_CODE"
echo $MORSE_CODE > /proc/morse
echo " "
dmesg


