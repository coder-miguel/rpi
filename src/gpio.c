//=========================================//
//   Title:  gpio.c                        //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#include <gpio.h>

#ifdef DEBUG
    #include <stdlib.h>
    #include <string.h>
    #ifdef _WIN32
        void sleep(nanos delay){
            int i = 0;
            while ( i < delay){
                i+=100;
            }
            return;
        }
    #elif __linux__
        #include <sys/time.h>
        void get_time(nanos *clk){
            struct timeval tv;
            gettimeofday(&tv, 0);
            *clk = ((tv.tv_sec * 1000000) + tv.tv_usec) & 0xFFFFFFFF;
        }
        void sleep(nanos delay){
            nanos* systime = (nanos*)malloc(sizeof(nanos));
            get_time(systime);
            nanos initial_time = *systime;
            while(((*systime) - initial_time) < delay){
                get_time(systime);
            }
            free(systime);
            return;
        }
    #endif
#else
    void sleep(nanos delay){
        nanos initial_time = read(BCM_TIMER);        // Get the current time in μs
        while((read(BCM_TIMER) - initial_time) < delay); // Wait for the amount of time
        return;
    }
#endif

void fsel(pin_t pin, fsel_t mode){
    int group = pin/10;
    int mod = pin%10;
    int value = 0;
    switch (group){
        case 0:
            value = read(GPFSEL0) & ~((0b111)<<(3*mod));
            write(GPFSEL0, value | ((mode&0b111)<<(3*mod)));
            break;
        case 1:
            value = read(GPFSEL1) & ~((0b111)<<(3*mod));
            write(GPFSEL1, value | ((mode&0b111)<<(3*mod)));
            break;
        case 2:
            value = read(GPFSEL2) & ~((0b111)<<(3*mod));
            write(GPFSEL2, value | ((mode&0b111)<<(3*mod)));
            break;
        case 3:
            value = read(GPFSEL3) & ~((0b111)<<(3*mod));
            write(GPFSEL3, value | ((mode&0b111)<<(3*mod)));
            break;
        case 4:
            value = read(GPFSEL4) & ~((0b111)<<(3*mod));
            write(GPFSEL4, value | ((mode&0b111)<<(3*mod)));
            break;
        case 5:
            value = read(GPFSEL5) & ~((0b111)<<(3*mod));
            write(GPFSEL5, value | ((mode&0b111)<<(3*mod)));
            break;
        default:
            break;
    }
}
void gpio_set(pin_t pin){
    if (pin >= 0 && pin <= 31){
        write(GPSET0, SET << pin);
    } else if (pin >= 32 && pin <= 52){
        write(GPSET1, SET << (pin-32));
    }
}
void gpio_clr(pin_t pin){
    if (pin >= 0 && pin <= 31){
        write(GPCLR0, SET << pin);
    } else if (pin >= 32 && pin <= 52){
        write(GPCLR1, SET << (pin-32));
    }
}
void blink(pin_t pin, nanos delay){
    if (pin >= 0 && pin <= 52) {
        gpio_set(pin);
        sleep(delay/2);
        gpio_clr(pin);
        sleep(delay/2);
    }
}
