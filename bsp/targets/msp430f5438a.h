#ifndef TARGETS_MSP430F5438A_H_
#define TARGETS_MSP430F5438A_H_

//Libraries
#include <stdint.h>


//Processor
#include <msp430.h>
#include "msp430f5438a_demo.h"


//Project
#include "../../globals.h"
#include "../clocks.h"


//Radio
#include "../radios/cc1200.h"
#include "../radios/cc1200_reg_config.h"


//Globals
extern void msp430f5438a_init(void);
extern void msp430f5438a_enable_interrupts(void);
extern void msp430f5438a_clocks_init(void);
extern void msp430f5438a_gpio_init(void);
extern void msp430f5438a_timers_init(void);

extern void msp430f5438a_radio_spi_begin(void);
extern void msp430f5438a_radio_spi_tx(uint8_t x);
extern void msp430f5438a_radio_spi_wait_done(void);
extern void msp430f5438a_radio_spi_rx(void);
extern void msp430f5438a_radio_spi_wait_miso_low(uint8_t x);
extern void msp430f5438a_radio_spi_end(void);
extern void msp430f5438a_radio_spi_hw_reset(void);
extern void msp430f5438a_radio_spi_wait_miso_high(uint8_t x);
extern void msp430f5438a_radio_spi_init(void);
extern void msp430f5438a_radio_gpio_init(void);


#endif /* TARGETS_MSP430F5438A_H_ */

