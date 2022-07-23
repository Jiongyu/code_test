# Comment/uncomment the following line to disable/enable debugging
# DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
  	DEBFLAGS = -O -g -Wall -Werror -Wno-unused -DMODULE_DEBUG # "-O" is needed to expand inlines
	EXTRA_CFLAGS += -DMODULE_DEBUG

else
  	DEBFLAGS = -O2
endif

CFLAGS += $(DEBFLAGS)
CFLAGS += -I..

obj-m	:= charDriver.o

APP_GCC := gcc
APP := ./charDriverApp
APP_SOURCE := ./charDriverApp.c

# KERNELDIR := /home/jony/linux_data/linux_source_code/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
KERNELDIR 		:= /home/jony/software/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
CURRENT_PATH    := $(shell pwd)

build: kernel_modules

kernel_modules:
	CONFIG_MODULE_SIG=n
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) modules
	${APP_GCC} ${APP_SOURCE} -o ${APP} ${CFLAGS}

build_app:
	${APP_GCC} ${APP_SOURCE} -o ${APP} ${CFLAGS}

clean:
	$(MAKE) -C $(KERNELDIR) M=$(CURRENT_PATH) clean
	rm -rf ${APP}

clean_app:
	rm -rf ${APP}

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
	include .depend
endif

