#ifndef TARGETS_MCU_H_
#define TARGETS_MCU_H_

//Processor Selection                                                         (done this way to make project visually cleanest)
//#define   TARGET_SEL_CC2541                                                /* final target                                         */
#define     TARGET_SEL_MSP430F5438A                                          /* starting dev platform                                */
//#define   TARGET_SEL_MSP430F5529                                           /* shared dev example-platform                          */

//Project
#ifdef TARGET_SEL_MSP430F5438A
    #include "targets/msp430f5438a.h"
    #define mcu_radio_spi_begin                 msp430f5438a_radio_spi_begin
    #define mcu_radio_spi_tx                    msp430f5438a_radio_spi_tx
    #define mcu_radio_spi_wait_done             msp430f5438a_radio_spi_wait_done
    #define mcu_radio_spi_rx                    msp430f5438a_radio_spi_rx
    #define mcu_radio_spi_wait_miso_low         msp430f5438a_radio_spi_wait_miso_low
    #define mcu_radio_spi_end                   msp430f5438a_radio_spi_end
    #define mcu_radio_hw_reset                  msp430f5438a_radio_hw_reset
    #define mcu_radio_sw_reset                  msp430f5438a_radio_sw_reset
    #define mcu_radio_spi_wait_for_miso_low     msp430f5438a_radio_spi_wait_for_miso_low
    #define mcu_radio_spi_init                  msp430f5438a_radio_spi_init
    #define mcu_radio_gpio_init                 msp430f5438a_radio_gpio_init

    #define mcu_init                            msp430f5438a_init
    #define mcu_enable_interrupts               msp430f5438a_enable_interrupts
    #define mcu_demo                            msp430f5438a_demo

    #define gpio_init                           msp430f5438a_gpio_init
    #define clocks_init                         msp430f5438a_clocks_init
    #define timers_init                         msp430f5438a_timers_init
#endif


//Globals
extern void mcu_init(void);
extern void mcu_enable_interrupts(void);
extern void mcu_demo(void);

extern void mcu_radio_spi_begin(void);
extern void mcu_radio_spi_tx(uint8_t x);
extern void mcu_radio_spi_wait_done(void);
extern uint8_t mcu_radio_spi_rx(void);
extern void mcu_radio_spi_wait_miso_low(void);
extern void mcu_radio_spi_end(void);
extern void mcu_radio_hw_reset(void);
extern void mcu_radio_sw_reset(void);
extern void mcu_radio_spi_wait_for_miso_low(void);
extern void mcu_radio_spi_init(void);
extern void mcu_radio_gpio_init(void);

extern void gpio_init(void);
extern void clocks_init(void);
extern void timers_init(void);

#endif /* TARGETS_MCU_H_ */

