obj-m += hello-1.o

KDIR ?= ../../linux-2.6.32 
PWD = $(CURDIR)

all: 
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=i386 modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) ARCH=i386 clean
