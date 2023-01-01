//=========================================//
//   Title:  io.h                          //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef IO
#define IO

#include <bcm283x.h>
#include <inttypes.h>
#include <stdbool.h>

typedef uint32_t pireg32_t;
typedef uint32_t piaddr32_t;
typedef uint32_t nanos;

#define NANOS_1     1
#define NANOS_10    10
#define NANOS_100   100
#define MILLIS_1    1000
#define MILLIS_10   (10 * 1000)
#define MILLIS_100  (100 * 1000)
#define MILLIS_1000 (1000 * 1000)
#define SECONDS_1   (1000 * 1000)

#define BIC(word, mask) (word) & ~(mask)
#define AND(word, mask) (word) &  (mask)
#define ORR(word, mask) (word) |  (mask)
#define XOR(word, mask) (word) ^  (mask)
#define NOT(word) ~(word)

void mmio_init();
/**
 * Parameters:
 *      - addr : uint32_t
 *      - data : uint32_t
 * 
 * Purpose:
 * Do a volatile write to an address on the pi */
void write(piaddr32_t addr, pireg32_t data);
/**
 * Parameters:
 *      - addr : uint32_t
 * 
 * Return:
 *      - The value at the address
 * Purpose:
 * Do a volatile read from an address on the pi */
pireg32_t read(piaddr32_t addr);

#endif
