//=========================================//
//   Title:  mmio.h                        //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef MMIO
#define MMIO
#include <rpi.h>
#include <inttypes.h>
#include <stdbool.h>

#define PI_BREAK asm volatile("brk #0");

#ifndef RPI_VERSION
    #define MMIO_BASE         (0x20000000)
#else
    #if RPI_VERSION==0 || RPI_VERSION==1 || RPI_VERSION==2
        #define MMIO_BASE         (0x20000000)
    #elif RPI_VERSION==3
        #define MMIO_BASE         (0x3f000000)
    #elif RPI_VERSION==4
        #define MMIO_BASE         (0xfe000000)
    #else
        #define MMIO_BASE         (0x20000000)
    #endif
#endif

#define GPIO_OFFSET         (0x200000)
#define UART_OFFSET         (0x201000)
#define PWM_OFFSET          (0x20c000)
#define CLKPWM_OFFSET       (0x1010a0)
#define BCMTIMER_OFFSET     (0x003004)
#define MBOX_OFFSET           (0xb880)

#define NANOS_1     1
#define NANOS_10    10
#define NANOS_100   100
#define MILLIS_1    1000
#define MILLIS_10   (10 * 1000)
#define MILLIS_100  (100 * 1000)
#define MILLIS_1000 (1000 * 1000)
#define SECONDS_1   (1000 * 1000)

typedef uint32_t pireg32_t;
typedef uint32_t piaddr32_t;
typedef uint32_t nanos;

#define BIC(word, mask) (word) & ~(mask)
#define AND(word, mask) (word) &  (mask)
#define ORR(word, mask) (word) |  (mask)
#define XOR(word, mask) (word) ^  (mask)
#define NOT(word) ~(word)

/**
 * @brief Not yet implemented
 * 
 */
void mmio_init();
/**
 * @brief Do a volatile write to an address
 * 
 * @param addr The physical address on the Pi
 * @param data The data to write
 */
void write(piaddr32_t addr, pireg32_t data);
/**
 * @brief Do a volatile read from an address
 * 
 * @param addr The physical address on the Pi
 * @return pireg32_t - The data read from that address
 */
pireg32_t read(piaddr32_t addr);

#endif
