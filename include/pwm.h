//=========================================//
//   Title:  pwm.h                         //
//  Author:  Miguel                        //
//    Date:  02/07/2023                    //
// Version:  2                             //
//   Notes:  Ref BCM2835-ARM-PERIFERALS    //
//=========================================//
#ifndef PWM
#define PWM

#include <mmio.h>
#include <gpio.h>

#define PWM_BASE      (MMIO_BASE | PWM_OFFSET)
#define PWM_CTL       (PWM_BASE | 0x00)
#define PWM_STA       (PWM_BASE | 0x04)
#define PWM_DMAC      (PWM_BASE | 0x08)
#define PWM_RNG1      (PWM_BASE | 0x10)
#define PWM_DAT1      (PWM_BASE | 0x14)
#define PWM_FIF1      (PWM_BASE | 0x18)
#define PWM_RNG2      (PWM_BASE | 0x20)
#define PWM_DAT2      (PWM_BASE | 0x24)

#define PWM_CLK         (MMIO_BASE | CLKPWM_OFFSET)
#define PWM_DIV         (PWM_CLK   | 0x04)


#define PWM_CLK_BUSY    (1<<7)
#define PWM_CLK_KILL    (1<<5)
#define PWM_CLK_ENAB    (1<<4)

#define PWM_FREQ    19200000

#define PWM_CLRF    (1<<6)
#define PWM_MSEN2   (1<<15)
#define PWM_USEF2   (1<<13)
#define PWM_POLA2   (1<<12)
#define PWM_SBIT2   (1<<11)
#define PWM_RPTL2   (1<<10)
#define PWM_MODE2   (1<<9)
#define PWM_PWEN2   (1<<8)
#define PWM_MSEN1   (1<<7)
#define PWM_USEF1   (1<<5)
#define PWM_POLA1   (1<<4)
#define PWM_SBIT1   (1<<3)
#define PWM_RPTL1   (1<<2)
#define PWM_MODE1   (1<<1)
#define PWM_PWEN1   (1<<0)

#define PWM_STA_STA4 (1<<12)
#define PWM_STA_STA3 (1<<11)
#define PWM_STA_STA2 (1<<10)
#define PWM_STA_STA1 (1<<9)
#define PWM_STA_BERR (1<<8)
#define PWM_STA_GAP4 (1<<7)
#define PWM_STA_GAP3 (1<<6)
#define PWM_STA_GAP2 (1<<5)
#define PWM_STA_GAP1 (1<<4)
#define PWM_STA_RERR (1<<3)
#define PWM_STA_WERR (1<<2)
#define PWM_STA_EMPT (1<<1)
#define PWM_STA_FULL (1<<0)

void pwm_init(float freq, pireg32_t range, pireg32_t pwm_options, pireg32_t clk_options);
void pwm_rng(uint8_t channel, pireg32_t range);
void pwm_set(uint8_t channel, pireg32_t data);
void pwm_push(pireg32_t data);
bool pwm_fifo_rerr();
bool pwm_fifo_werr();
bool pwm_fifo_empty();
bool pwm_fifo_full();
bool _pwm_sta_flag(pireg32_t sta);
float _src_freq(clkmode_t mode);
#endif
