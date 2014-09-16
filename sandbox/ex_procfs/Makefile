obj-m += procfs1.o
obj-m += procfs2.o
obj-m += procfs3.o
obj-m += procfs4.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	# make -C /usr/src/linux-`uname -r` SUBDIRS=$PWD modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	# make -C /usr/src/linux-`uname -r` SUBDIRS=$PWD clean

