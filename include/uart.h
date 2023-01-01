//=========================================//
//   Title:  uart.h                        //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef UART
#define UART
#include <gpio.h>

#define UART_BASE     (MMIO_BASE | UART_OFFSET)
#define UART_DR       (UART_BASE | 0x00)
#define UART_RSRECR   (UART_BASE | 0x04)
#define UART_FR       (UART_BASE | 0x18)
#define UART_ILPR     (UART_BASE | 0x20)
#define UART_IBRD     (UART_BASE | 0x24)
#define UART_FBRD     (UART_BASE | 0x28)
#define UART_LCRH     (UART_BASE | 0x2c)
#define UART_CR       (UART_BASE | 0x30)
#define UART_IFLS     (UART_BASE | 0x34)
#define UART_IMSC     (UART_BASE | 0x38)
#define UART_RIS      (UART_BASE | 0x3c)
#define UART_MIS      (UART_BASE | 0x40)
#define UART_ICR      (UART_BASE | 0x44)
#define UART_DMACR    (UART_BASE | 0x48)
#define UART_ITCR     (UART_BASE | 0x80)
#define UART_ITIP     (UART_BASE | 0x84)
#define UART_ITOP     (UART_BASE | 0x88)
#define UART_TDR      (UART_BASE | 0x8c)

void uart_init(pireg32_t brd);
void uart_putc(char c);
char uart_getc();
void uart_puts(const char* str);

#endif
