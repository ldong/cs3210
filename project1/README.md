# README

``` bash
lsmod
insmod
rmmod
```

## Running it manually
```
sudo rmmod morse_module.

make

sudo insmod morse_module.ko

sudo su

# ".... . .-.. .-.. --- .-- --- .-. .-.. -.." means helloworld

echo ".... . .-.. .-.. --- .-- --- .-. .-.. -.." > /proc/morse2txt

dmesg

cat /proc/morse2txt
```

## TODO

How to benchmark its performance?

`perf record -g -e cpu-clock /proc/morse2txt`

