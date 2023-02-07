//=========================================//
//   Title:  uart.h                        //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
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

/**
 * @brief Initalize the Raspberry Pi UART with specific Baud
 * 
 * @param brd Baud Rate (e.g. 115200)
 */
void uart_init(pireg32_t brd);
/**
 * @brief Put a character onto the UART TX line
 * 
 * @param c The character to put onto UART TX
 */
void uart_putc(char c);
/**
 * @brief Get a char on the UART RX line
 * 
 * @return A char received from UART RX
 */
char uart_getc();
/**
 * @brief Put a string of characters onto the UART TX line
 * 
 * @param str The null-terminated string of characters to put onto UART TX
 */
void uart_puts(const char* str);

#endif
