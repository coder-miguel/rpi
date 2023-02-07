//=========================================//
//   Title:  rpi.h                         //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef RPI
#define RPI
#define _STRINGIZE(x) #x
#define _FN(x, y) y(x)
#define _STRINGIFY(x) _FN(x, _STRINGIZE)
    #ifndef RPI_VERSION
        #pragma message("Export system variable RPI")
        #pragma message("Example 1: make rpi4")
        #pragma message("Example 2: export RPI_VERSION=4 && make")
    #else
        #pragma message("RPI_VERSION: " _STRINGIFY(RPI_VERSION))
    #endif
#endif
