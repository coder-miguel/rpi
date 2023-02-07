# About
A boiler-plate for writing bare-metal raspberry pi with the C programming language.

The makefile currently only supports bash commands, so using bash and/or linux(wsl) environment is preferred.

Manual Compile commands below for Windows users

# Requirements
## Required
1. Cross Compiler (arm-none-eabi)
## Preferred
2. Linux (or WSL on windows)
3. GNU Make (with bash)
# Using Make
## Supports rpi0, rpi1, rpi2, rpi3, and rpi4
```
make rpi3
```
```
make rpi4
```
```
make rpi0
```
# Or Compile Manually
```bash
cd bin
```
```bash
arm-none-eabi-gcc -DRPI_VERSION=3 -mcpu=cortex-a53 -I ../include -c ../src/mmio.c ../src/gpio.c ../src/pwm.c ../src/uart.c ../src/start.c ../src/main.c
```
>*see Flags below for different versions
```bash
arm-none-eabi-gcc -T ../linker.ld -o kernel.elf mmio.o gpio.o pwm.o uart.o main.o start.o --freestanding -O2 -nostdlib -lgcc
```
```bash
arm-none-eabi-objcopy kernel.elf -O binary kernel.img
```
```
cd ../
```
## Flags for Different Pi Versions:
```
-DRPI_VERSION=0 -mcpu=arm1176jzf-s
-DRPI_VERSION=1 -mcpu=arm1176jzf-s
-DRPI_VERSION=2 -mcpu=cortex-a7
-DRPI_VERSION=3 -mcpu=cortex-a53
-DRPI_VERSION=4 -mcpu=cortex-a72
```
