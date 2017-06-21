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


#endif /* TARGETS_MSP430F5438A_H_ */

