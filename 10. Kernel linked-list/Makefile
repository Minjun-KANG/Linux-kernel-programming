#2017707007 Minjun-KANG Makefile

obj-m += test.o

#KDIR := /lib/modules/$(shell uname -r)/build
#PWD:=$(shell pwd)


all:
	#$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modlues
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	#rm -rf *.kr *.mod.* .*.cmd *.o
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


