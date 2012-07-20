 ##Makefile
# If KERNELRELEASE is defined, we've been invoked from the 
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m   := ex03_misc.o

# Otherwise we were called directly from the command
# line; invoke the kernel build system
else
	KERNEL_DIR ?= /lib/modules/`uname -r`/build
	MODULEDIR := $(shell pwd)

default:
	make -C $(KERNEL_DIR)  M=$(MODULEDIR) modules

endif

clean:
	rm -f *.o *.ko *.mod.c Module.* modules.*
