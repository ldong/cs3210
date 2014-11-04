Text to led
/media/realroot/code/kernel/text2gpio_procf

make
insmod text2gpio.ko
echo "hello" > /proc/text
echo "h" > /proc/text
rmmod text2gpio.ko
make clean

Led to text
/media/realroot/code/kernel/gpio2text

make
insmod gpio2text.ko
cat /proc/text_out
make clean


/media/realroot/code/chat
bash chat.sh

