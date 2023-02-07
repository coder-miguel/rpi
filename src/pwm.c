//=========================================//
//   Title:  pwm.c                         //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#include <pwm.h>

void pwm_init(float freq, pireg32_t range, pireg32_t pwm_options, pireg32_t clk_options){
    /*======================================
    *  Clock Procedure
    * ======================================
    *  1. Stop Clock
    *  2. Set Frequency
    *  3. Set Clock Options
    *  4. Start Clock
    * ====================================== */
    pireg32_t pwmclk = read(PWM_CLK);
    pwmclk = BIC(pwmclk, CLK_ENAB);
    while(read(PWM_CLK) & CLK_BUSY == CLK_BUSY) {}
    write(PWM_CLK, CLK_PASSWD | pwmclk);
    sleep(MILLIS_10);

    clk_options &= 0x70F;
    float targfreq = _src_freq(clk_options & 0xF)/freq;
    uint32_t divi = (uint32_t)(targfreq) & 0xFFF;
    uint32_t divf = ((uint32_t)((float)(targfreq-divi) * 1024)) & 0xFFF;
    while(read(PWM_CLK) & CLK_BUSY == CLK_BUSY) {}
    write(PWM_DIV, (CLK_PASSWD | (divi << 12) | (divf)));
    sleep(MILLIS_10);

    while(read(PWM_CLK) & CLK_BUSY == CLK_BUSY) {}
    write(PWM_CLK, (CLK_PASSWD | CLK_ENAB | clk_options));
    sleep(MILLIS_10);

    /*=====================================
    *  PWM Procedure
    * =====================================
    *  1. Set Ranges
    *  2. Set Options
    * ===================================== */
    write(PWM_RNG1, range);
    write(PWM_RNG2, range);
    write(PWM_CTL, pwm_options & 0xBFFF);
    sleep(MILLIS_10);
}
void pwm_rng(uint8_t channel, pireg32_t range){
    switch (channel){
        case 1:
            write(PWM_RNG1, range);
            break;
        case 2:
            write(PWM_RNG2, range);
            break;
        default:
            break;
    }
}
void pwm_set(uint8_t channel, pireg32_t data){
    switch (channel){
        case 1:
            write(PWM_DAT1, data);
            break;
        case 2:
            write(PWM_DAT2, data);
            break;
        default:
            break;
    }
}
void pwm_push(pireg32_t data){
    do {
        write(PWM_FIF1, data);
        sleep(MILLIS_1);
    } while (pwm_fifo_werr());
}
bool pwm_fifo_empty(){
    return _pwm_sta_flag(PWM_STA_EMPT);
}
bool pwm_fifo_full(){
    return _pwm_sta_flag(PWM_STA_FULL);
}
bool pwm_fifo_rerr(){
    pireg32_t rerr = _pwm_sta_flag(PWM_STA_RERR);
    write(PWM_STA, PWM_STA_RERR);
    return rerr;
}
bool pwm_fifo_werr(){
    pireg32_t rerr = _pwm_sta_flag(PWM_STA_WERR);
    write(PWM_STA, PWM_STA_WERR);
    return rerr;
}
bool _pwm_sta_flag(pireg32_t sta){
    return (read(PWM_STA) & sta) == sta;
}
float _src_freq(clkmode_t mode){
    switch(mode){
        case CLK_GND:
            return 0.0;
            break;
        case CLK_OSCILLATOR:
            return 19.2;
            break;
        case CLK_TESTDEBUG0:
            return 0.0;
            break;
        case CLK_TESTDEBUG1:
            return 0.0;
            break;
        case CLK_PLLA:
            return 0.0;
            break;
        case CLK_PLLC:
            return 1000.0;
            break;
        case CLK_PLLD:
            return 500.0;
            break;
        case CLK_HDMIAUX:
            return 216.0;
            break;
        default:
            return 0.0;
    }
}
