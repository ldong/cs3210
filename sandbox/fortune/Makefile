obj-m += fortune.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	# make -C /usr/src/linux-`uname -r` SUBDIRS=$PWD modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	# make -C /usr/src/linux-`uname -r` SUBDIRS=$PWD clean

