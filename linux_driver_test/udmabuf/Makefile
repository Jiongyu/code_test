HOST_ARCH       ?= $(shell uname -m | sed -e s/arm.*/arm/ -e s/aarch64.*/arm64/)
ARCH            ?= $(shell uname -m | sed -e s/arm.*/arm/ -e s/aarch64.*/arm64/)

ifdef KERNEL_SRC
  KERNEL_SRC_DIR  := $(KERNEL_SRC)
else
  KERNEL_SRC_DIR  ?= /lib/modules/$(shell uname -r)/build
endif

KERNEL_SRC_DIR = /home/jony/software/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek
ARCH = arm

ifeq ($(ARCH), arm)
 ifneq ($(HOST_ARCH), arm)
   CROSS_COMPILE  ?= arm-linux-gnueabihf-
 endif
endif
ifeq ($(ARCH), arm64)
 ifneq ($(HOST_ARCH), arm64)
   CROSS_COMPILE  ?= aarch64-linux-gnu-
 endif
endif

u-dma-buf-obj           := u-dma-buf.o
obj-$(CONFIG_U_DMA_BUF) += $(u-dma-buf-obj)

ifndef UDMABUF_MAKE_TARGET
  KERNEL_VERSION_LT_5 ?= $(shell awk '/^VERSION/{print int($$3) < 5}' $(KERNEL_SRC_DIR)/Makefile)
  ifeq ($(KERNEL_VERSION_LT_5), 1)
    UDMABUF_MAKE_TARGET ?= modules
  else
    UDMABUF_MAKE_TARGET ?= u-dma-buf.ko
  endif
endif

APP_SRC     := u-dma-buf.c
APP_TARGET  := dmaTest

all:
	$(MAKE) -C $(KERNEL_SRC_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) obj-m=$(u-dma-buf-obj) $(UDMABUF_MAKE_TARGET)
  $(CROSS_COMPILE)gcc -o $(APP_TARGET) $(APP_SRC)

modules_install:
	$(MAKE) -C $(KERNEL_SRC_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) obj-m=$(u-dma-buf-obj) modules_install

clean:
	$(MAKE) -C $(KERNEL_SRC_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) clean
  rm $(APP_TARGET)

