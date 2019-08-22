MODULENAME=helloworld

obj-m += hello-1.o

all:
	make -C /lib/modules/4.4.0-47-generic/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.4.0-47-generic/build M=$(PWD) clean

install:
	insmod $(MODULENAME).ko
	chmod 666 /dev/$(MODULENAME)

uninstall: 
	sudo rmmod $(MODULENAME)
