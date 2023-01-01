//=========================================//
//   Title:  bcm2837.h                     //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef BCM2837
#define BCM2837

#define PI3_BREAK asm volatile("brk #0");

// Periferal Base and its common offsets
#define MMIO_BASE         (0x3f000000)
#define GPIO_OFFSET         (0x200000)
#define UART_OFFSET         (0x201000)
#define PWM_OFFSET          (0x20c000)
#define CLKPWM_OFFSET       (0x1010a0)
#define BCMTIMER_OFFSET     (0x003004)
#define MBOX_OFFSET           (0xb880)

#endif
