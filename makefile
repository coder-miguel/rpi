#@//=========================================//
#@//                                         //
#@//   Title:  makefile                      //
#@//  Author:  Miguel                        //
#@//    Date:  02/07/2023                    //
#@// Version:  2                             //
#@//   Notes:  GNU Arm Embedded Toolchain    //
#@//=========================================//
projdir = $(shell pwd)
bindir = $(projdir)/bin
srcdir = $(projdir)/src
includedir = $(projdir)/include

code  := $(shell find $(srcdir) -type f -name '*.c' -exec basename {} .c \;)

bin    = $(bindir)/kernel.img
elf    = $(bindir)/kernel.elf
src   := $(patsubst %, $(srcdir)/%.c, $(code))
asm   := $(patsubst %, $(srcdir)/%.s, $(code))
obj   := $(patsubst %, $(bindir)/%.o, $(code))

ifeq ($(RPI_VERSION), Zero)
	rpiv = -DRPI_VERSION=0
	mcpu = -mcpu=arm1176jzf-s
else ifeq ($(RPI_VERSION), 0)
	rpiv = -DRPI_VERSION=0
	mcpu = -mcpu=arm1176jzf-s
else ifeq ($(RPI_VERSION), 1)
	rpiv = -DRPI_VERSION=1
	mcpu = -mcpu=arm1176jzf-s
else ifeq ($(RPI_VERSION), 2)
	rpiv = -DRPI_VERSION=2
	mcpu = -mcpu=cortex-a7
else ifeq ($(RPI_VERSION), 3)
	rpiv = -DRPI_VERSION=3
	mcpu = -mcpu=cortex-a53
else ifeq ($(RPI_VERSION), 4)
	rpiv = -DRPI_VERSION=4
	mcpu = -mcpu=cortex-a72
else
	rpiv = -DRPI_VERSION=$(RPI_VERSION)
endif

$(bin) : $(elf)
	arm-none-eabi-objcopy $(elf) -O binary $(bin)
	rm $(elf)

$(elf) : $(obj)
	arm-none-eabi-gcc -T linker.ld -o $(elf) $(obj) -ffreestanding -O2 -nostdlib -lgcc
	rm $(obj)

$(obj) : $(src)
	cd $(bindir) && arm-none-eabi-gcc $(rpiv) $(mcpu) -I $(includedir) -c $(src)

rpi0:
	export RPI_VERSION=0&&make
rpi1:
	export RPI_VERSION=1&&make
rpi2:
	export RPI_VERSION=2&&make
rpi3:
	export RPI_VERSION=3&&make
rpi4:
	export RPI_VERSION=4&&make
clean:
	rm -rf $(bindir)/*
