//=========================================//
//   Title:  gpio.h                        //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef GPIO
#define GPIO
#include <mmio.h>

// Address to the BCM Timers
#define BCM_TIMER     (MMIO_BASE | BCMTIMER_OFFSET)

// GPIO Addressess
#define GPIO_BASE     (MMIO_BASE | GPIO_OFFSET)
#define GPIO_SIZE     (0xa0)
#define GPFSEL0       (GPIO_BASE | 0x00)
#define GPFSEL1       (GPIO_BASE | 0x04)
#define GPFSEL2       (GPIO_BASE | 0x08)
#define GPFSEL3       (GPIO_BASE | 0x0c)
#define GPFSEL4       (GPIO_BASE | 0x10)
#define GPFSEL5       (GPIO_BASE | 0x14)
#define GPSET0        (GPIO_BASE | 0x1c)
#define GPSET1        (GPIO_BASE | 0x20)
#define GPCLR0        (GPIO_BASE | 0x28)
#define GPCLR1        (GPIO_BASE | 0x2c)
#define GPLEV0        (GPIO_BASE | 0x34)
#define GPLEV1        (GPIO_BASE | 0x38)
#define GPEDS0        (GPIO_BASE | 0x40)
#define GPEDS1        (GPIO_BASE | 0x44)
#define GPREN0        (GPIO_BASE | 0x4c)
#define GPREN1        (GPIO_BASE | 0x50)
#define GPFEN0        (GPIO_BASE | 0x58)
#define GPFEN1        (GPIO_BASE | 0x5c)
#define GPHEN0        (GPIO_BASE | 0x64)
#define GPHEN1        (GPIO_BASE | 0x68)
#define GPLEN0        (GPIO_BASE | 0x70)
#define GPLEN1        (GPIO_BASE | 0x74)
#define GPAREN0       (GPIO_BASE | 0x7c)
#define GPAREN1       (GPIO_BASE | 0x80)
#define GPAFEN0       (GPIO_BASE | 0x88)
#define GPAFEN1       (GPIO_BASE | 0x8c)
#define GPPUD         (GPIO_BASE | 0x94)
#define GPPUDCLK0     (GPIO_BASE | 0x98)
#define GPPUDCLK1     (GPIO_BASE | 0x9c)
#define GPTEST        (GPIO_BASE | 0xb0)

// Single bit options
#define UNSET 0
#define SET 1
#define DISABLE 0
#define ENABLE  1
#define EVENT_NOT_DETECTED 0
#define EVENT_DETECTED 1
#define LOW  0
#define HIGH 1

// Clock
#define CLK_PASSWD      (0x5A << 24)
#define CLK_MASH(i)     ((i&0b11) << 9)
#define CLK_FLIP        (1 << 8)
#define CLK_BUSY        (1 << 7)
#define CLK_KILL        (1 << 5)
#define CLK_ENAB        (1 << 4)
#define CLK_SRC_GND     (0 << 0)
#define CLK_SRC_OSCI    (1 << 0)
#define CLK_SRC_TST0    (2 << 0)
#define CLK_SRC_TST1    (3 << 0)
#define CLK_SRC_PLLA    (4 << 0)
#define CLK_SRC_PLLC    (5 << 0)
#define CLK_SRC_PLLD    (6 << 0)
#define CLK_SRC_HDMI    (7 << 0)

// Fsel functions (3 bits)
typedef enum FSEL_T{FSEL_IN=0, FSEL_OUT=1, FSEL_ALT5=2,FSEL_ALT4=3,
        FSEL_ALT0=4, FSEL_ALT1=5, FSEL_ALT2=6, FSEL_ALT3=7} fsel_t;
typedef enum PIN_T{PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8, PIN_9,
        PIN_10, PIN_11, PIN_12, PIN_13, PIN_14, PIN_15, PIN_16, PIN_17, PIN_18, PIN_19,
        PIN_20, PIN_21, PIN_22, PIN_23, PIN_24, PIN_25, PIN_26, PIN_27, PIN_28, PIN_29,
        PIN_30, PIN_31, PIN_32, PIN_33, PIN_34, PIN_35, PIN_36, PIN_37, PIN_38, PIN_39,
        PIN_40, PIN_41, PIN_42, PIN_43, PIN_44, PIN_45, PIN_46, PIN_47, PIN_48, PIN_49,
        PIN_50, PIN_51, PIN_52} pin_t;
// Pull Up/Down Options (2 bits)
typedef enum PUD_T{PUD_OFF=0, PUD_DOWN=1, PUD_UP=2} pud_t;
// Clock src (3 bits)
typedef enum CLKMODE_T{CLK_GND=0, CLK_OSCILLATOR=1, CLK_TESTDEBUG0=2, CLK_TESTDEBUG1=3,
        CLK_PLLA=4, CLK_PLLC=5, CLK_PLLD=6, CLK_HDMIAUX=7} clkmode_t;

// Below are the data structures for the GPIO, PWM and CLK types. The data structures are
// defined in BCM2835 Manual


/*____________________________________Functions_____________________________________*/
void gpio_set(pin_t pin);
void gpio_clr(pin_t pin);
/**
 * Parameters:
 *      - pin (0..52)
 *      - delay (μs)
 * Return:
 *      - void
 * 
 * Purpose:
 * Sends a pulse to the selected pin that spans a time of {delay} in μs*/
void blink(pin_t pin, nanos delay);
/**
 * Parameters:
 *      - pin (0..52)
 *      - mode (IN, OUT, ALT0, ALT1, ALT2, ALT3, ALT4, ALT5)
 * Return:
 *      - void
 * Purpose:
 * Sets the mode of the specified GPIO pin */
void fsel(pin_t pin, fsel_t mode);
/**
 * Parameters:
 *      - delay : nanos (μs)
 * 
 * Return:
 *      - void
 * Purpose:
 * Pauses the thread using a loop for the time delay in NANOSECONDS */
void sleep(nanos delay);
#endif
