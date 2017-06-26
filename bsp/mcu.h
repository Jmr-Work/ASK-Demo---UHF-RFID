#ifndef TARGETS_MCU_H_
#define TARGETS_MCU_H_

//Processor Selection                                                         (done this way to make project visually cleanest)
//#define   TARGET_SEL_CC2541                                                /* final target                                         */
#define     TARGET_SEL_MSP430F5438A                                          /* starting dev platform                                */
//#define   TARGET_SEL_MSP430F5529                                           /* shared dev example-platform                          */

//Project
#ifdef TARGET_SEL_MSP430F5438A
    #include "targets/msp430f5438a.h"
    #define mcu_radio_spi_begin             msp430f5438a_radio_spi_begin
    #define mcu_radio_spi_tx                msp430f5438a_radio_spi_tx
    #define mcu_radio_spi_wait_done         msp430f5438a_radio_spi_wait_done
    #define mcu_radio_spi_rx                msp430f5438a_radio_spi_rx
    #define mcu_radio_spi_wait_miso_low     msp430f5438a_radio_spi_wait_miso_low
    #define mcu_radio_spi_end               msp430f5438a_radio_spi_end
    #define mcu_radio_spi_hw_reset          msp430f5438a_radio_spi_hw_reset
    #define mcu_radio_spi_wait_miso_high    msp430f5438a_radio_spi_wait_miso_high
    #define mcu_radio_spi_init              msp430f5438a_radio_spi_init
    #define mcu_radio_gpio_init             msp430f5438a_radio_gpio_init
#endif



//Globals
extern void mcu_init(void);
extern void mcu_enable_interrupts(void);
extern void mcu_demo(void);


//@open  Pin Mappings (ports & pins by name)
extern void mcu_radio_spi_begin(void);
extern void mcu_radio_spi_tx(uint8_t x);
extern void mcu_radio_spi_wait_done(void);
extern void mcu_radio_spi_rx(void);
extern void mcu_radio_spi_wait_miso_low(uint8_t x);
extern void mcu_radio_spi_end(void);
extern void mcu_radio_spi_hw_reset(void);
extern void mcu_radio_spi_wait_miso_high(uint8_t x);
extern void mcu_radio_spi_init(void);
extern void mcu_radio_gpio_init(void);

#endif /* TARGETS_MCU_H_ */

