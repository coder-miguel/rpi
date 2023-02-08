//=========================================//
//   Title:  main.c                        //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//=========================================//
#include <gpio.h>
#include <pwm.h>
#include <uart.h>

void main(){

    // initialize UART with 115200Bd (Baud)
    uart_init(115200);
    uart_puts("UART Initialized\r\n");

    // initialize Pulse Width Modulation (PWM) with freq=9.6MHz range=255
    pwm_init(9.6, 255,
        PWM_MSEN2|PWM_MSEN1|PWM_PWEN2|PWM_PWEN1,
        CLK_MASH(0)|CLK_SRC_OSCI);

    uart_puts("PWM Initialized\r\n");

    fsel(12, FSEL_ALT0);
    uart_puts("GPIO pin 12 set to ALT0 (PWM Channel 1)\r\n");
    fsel(21, FSEL_OUT);
    uart_puts("GPIO pin 21 set to Output\r\n");
    fsel(26, FSEL_IN);
    uart_puts("GPIO pin 26 set to Input\r\n");
    write(GPREN0, 1<<26);
    uart_puts("Rising Edge Detection enabled on GPIO pin 26\r\n");

    // Variables
    char dat = 0;   // Used for PWM value, min=0 max=255
    bool pin21_state = false; // Keep track of the state of pin 21
    pireg32_t gpeds0_register = 0; // Varibale to store reads from Event Detect Register
    nanos timenow = read(BCM_TIMER); // Timer
    nanos timeprev = timenow;        // Timer

    // main Loop
    while(1){
        // default delay of each loop
        sleep(2*MILLIS_10);

        // toggle pin 21 every 1 second
        timenow = read(BCM_TIMER);
        if ((timenow - timeprev) > SECONDS_1){
            timeprev = timenow;
            if (pin21_state)
                gpio_set(21);
            else
                gpio_clr(21);
            pin21_state = !pin21_state;
        }


        // check if button was pressed
        gpeds0_register = read(GPEDS0);     // read the Event Detect Register (GPIO pins 0-31)
        if ((gpeds0_register >> 26) & 0x1){  // isolate pin 26 bit position (check GPIO 26 activitiy)
            uart_puts("Button 26 pressed");
            write(GPEDS0, 0xffffffff);      // clean EDS register
        }

        // gradually increase value of PWM on Channel 1
        pwm_set(1, dat);
        dat += 1;
        if (dat == 255) // Reset when it reaches maximum value (should overflow anyway)
            dat = 0;
    }
}
