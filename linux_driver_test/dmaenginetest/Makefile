# Comment/uncomment the following line to disable/enable debugging
DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  	DEBFLAGS = -O -g  # "-O" is needed to expand inlines
	EXTRA_CFLAGS += -DMODULE_DEBUG

else
  	DEBFLAGS = -O2 
endif

EXTRA_CFLAGS += $(DEBFLAGS) -Wall -Werror -Wno-unused -Wno-format
EXTRA_CFLAGS += -I..

obj-m	:= dmaengineDriverTest.o

APP_GCC := arm-linux-gnueabihf-gcc
APP := ./dmaengineDriverTestApp
APP_SOURCE := ./dmaengineDriverTestApp.c

# KERNELDIR := /home/jony/linux_data/linux_source_code/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
KERNELDIR 		:= /home/jony/software/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
CURRENT_PATH    := $(shell pwd)

build: kernel_modules

kernel_modules:
	CONFIG_MODULE_SIG=n
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
	${APP_GCC} ${APP_SOURCE} -o ${APP} ${EXTRA_CFLAGS}

build_app:
	${APP_GCC} ${APP_SOURCE} -o ${APP} ${EXTRA_CFLAGS}

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
	rm -rf ${APP}

clean_app:
	rm -rf ${APP}

depend .depend dep:
	$(CC) $(EXTRA_CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
	include .depend
endif
