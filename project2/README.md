# README

Authors:
* [xinyichen](https://github.com/xinyichen)
* [ldong](https://github.com/ldong)

## Setup

1. Install TU-S9 serial cable [driver](http://www.trendnet.com/support/supportdetail.asp?prod=265_TU-S9)
2. Connect `screen /dev/tty.usbserial 115200`
3. To close the connection `C-a :quit`
4. `screen -ls`
5. `screen -x screenID`

## Enter the Debian from Galileo

1. `F7`
2. `c`
3. `quit`
4. select **shell**
5. select **debian**

## Compile Kernel 3.8.7
[Kernel 3.8.7](https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.8.7.tar.gz)

```
wget https://www.kernel.org/pub/linux/kernel/v3.x/linux-3.8.7.tar.gz

/usr/src/kernels
apt-get install libncurses5-dev

```

## Light up a LED
```
echo 3 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio3/direction
echo 1 > /sys/class/gpio/gpio3/value
echo 0 > /sys/class/gpio/gpio3/value
```

## How to run
bash < <( curl -L https://raw.github.com/gist/73344/rcsetup )


# Download image

1. `cat Galileo_1.0.1_ZeroMQ_8GB.img.7z* > Galileo_1.0.1_ZeroMQ_8GB.img.7z`
2. Unarchive it and burn it using `dd` to your SD card
3. username: `root`, password: `a12345`


# Reference

[Intel Galileo - Programming GPIO From Linux](http://www.malinov.com/Home/sergey-s-blog/intelgalileo-programminggpiofromlinux)

[Toggling Arduino Pins from Linux](https://communities.intel.com/thread/46684)

[Screen Quick Reference](http://aperiodic.net/screen/quick_reference)

[Expand the root filesystem size](http://sourceforge.net/p/galileodebian/wiki/How%20to%20expand%20the%20root%20filesystem%20to%20use%20the%20entire%20SD%20card/)

[Linux Kernel 3.8.7 source tree](https://git.kernel.org/cgit/linux/kernel/git/stable/linux-stable.git/log/?id=refs/tags/v3.8.7)

[x86 版的 Arduino 来了，Intel Galileo 开发板的体验、分析和应用](http://bbsquark.eepw.com.cn/thread/34/1)

[第二十六章、Linux 核心編譯與管理](http://linux.vbird.org/linux_basic/0540kernel.php#kernel_source_install)

[How to Compile the Linux Kernel: 15 Steps - wikiHow](http://www.wikihow.com/Compile-the-Linux-Kernel)

[How to compile and install a new Linux kernel](http://www.berkes.ca/guides/linux_kernel.html)

[编译Linux内核(kernel)](http://www.douban.com/group/topic/27646661/)

[一個簡單的 Linux Kernel Module](http://wwssllabcd.github.io/blog/2012/11/13/how-to-make-linux-module/)

[How to compile and install a new Linux kernel](http://www.berkes.ca/guides/linux_kernel.html)

[Intel Galileo - Crashcourse Wiki](http://www.crashcourse.ca/wiki/index.php/Intel_Galileo)

[Installing ROS on Galileo](http://wiki.ros.org/IntelGalileo/Debian)

[Intel Galileo Full Featured Debian Linux Prebuilt Image](http://devgrapher.com/en/?p=497)

[Intel Galileo Download Center](https://downloadcenter.intel.com/Detail_Desc.aspx?DwnldID=23171#help)