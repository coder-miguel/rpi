//=========================================//
//   Title:  main.c                        //
//  Author:  Miguel                        //
//    Date:  12/31/2022                    //
// Version:  1                             //
//=========================================//
#include <rpi.h>

void main(){
    uart_init(115200);
    uart_puts("UART Initialized\r\n");
    pwm_init(9.6, 255,
        PWM_MSEN2|PWM_MSEN1|PWM_PWEN2|PWM_PWEN1,
        CLK_MASH(0)|CLK_SRC_OSCI);
    uart_puts("PWM Initialized\r\n");

    fsel(12, FSEL_ALT0); // pwm channel 1
    fsel(13, FSEL_ALT0); // pwm channel 2
    char dat1 = 0;
    char dir1 = 1;
    char dat2 = 127;
    char dir2 = -1;
    while(1) {
        sleep(2*MILLIS_10);

        pwm_wdat(1, dat1);
        pwm_wdat(2, dat2);
        dat1 += dir1;
        dat2 += dir2;
        if (dat1 == 127 || dat1 == 0)
            dir1 *= -1;
        if (dat2 == 127 || dat2 == 0)
            dir2 *= -1;
    }
}
