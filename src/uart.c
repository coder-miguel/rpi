//=========================================//
//   Title:  uart.c                        //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#include <uart.h>

void uart_init(pireg32_t brd){
    /*======================================
    *  UART Init
    * ======================================
    *  1. Stop the UART (CR)
    *  2. Set pins 14 and 15 to ALT 0 (fsel/PUD/PUDCLK0)
    *  3. Clear the UART Interrupt Clear Register (ICR)
    *  4. Set integer and fractional Baud Registers (IBRD/FBRD)
    *  5. Enable options in Line Control Register (LCRH)
    *  6. Mask out unused interrupts (IMSC)
    *  7. Set UART options and enable the UART (CR)
    * ====================================== */
    write(UART_CR,      0);                         sleep(MILLIS_100);
    fsel((pin_t)PIN_14, (fsel_t)FSEL_ALT0);
    fsel((pin_t)PIN_15, (fsel_t)FSEL_ALT0);
    write(GPPUD,        0);                         sleep(MILLIS_10);
    write(GPPUDCLK0,    ((1<<14)|(1<<15)));         sleep(MILLIS_10);
    write(GPPUDCLK0,    0x0);                       sleep(MILLIS_10);
    write(UART_ICR,     0x7FF);                     sleep(MILLIS_10);
    pireg32_t ibrd = 3000000 / brd; // ibrd = 48,000,000/(16 * brd)
    pireg32_t fbrd =                // fbrd = floor(64 * fractional + .5)
    ((64.0 * ((3000000.0 / brd) - ibrd)) + .5);
    write(UART_IBRD,    ibrd);                      sleep(MILLIS_10);
    write(UART_FBRD,    fbrd);                      sleep(MILLIS_10);
    write(UART_LCRH,    ((1<<4)|(1<<5)|(1<<6)));    sleep(MILLIS_10);
    write(UART_IMSC,
        ((1<<1)|(1<<4)|(1<<5)|(1<<6)|
        (1<<7)|(1<<8)|(1<<9)|(1<<10)));             sleep(MILLIS_100);
    write(UART_CR,      ((1<<8)|(1<<9)));           sleep(MILLIS_100);
    write(UART_CR,      ((1<<0)|(1<<8)|(1<<9)));    sleep(MILLIS_100);
}
void uart_putc(char c){
    while (read(UART_FR) & (1<<5)) {}   // Wait for UART to be ready for transmit
    write(UART_DR, (pireg32_t) c);      // Write to UART
}
char uart_getc(){
    while  (read(UART_FR) & (1<<4)) {}  // Wait for UART to receive a character
    return (read(UART_DR) & 0xFF);      // Read from UART
}
void uart_puts(const char* str){
    for (int i = 0; str[i] != '\0'; i ++)
        uart_putc((char)(str[i]));
}
