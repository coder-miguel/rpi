#@//=========================================//
#@//                                         //
#@//   Title:  makefile                      //
#@//  Author:  Miguel                        //
#@//    Date:  12/31/2022                    //
#@// Version:  1                             //
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

$(bin) : $(elf)
	touch $(elf)
	arm-none-eabi-objcopy $(elf) -O binary $(bin)
	rm $(obj) $(elf)
	touch $(bin)

$(elf) : $(obj)
	touch $(obj)
	arm-none-eabi-gcc -T linker.ld -o $(elf) $(obj) -ffreestanding -O2 -nostdlib -lgcc

$(obj) : $(src)
	
	cd $(bindir) && arm-none-eabi-gcc -I $(includedir) -c $(src) 

clean:
	- rm -rf $(bindir)/*
