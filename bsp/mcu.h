#ifndef TARGETS_MCU_H_
#define TARGETS_MCU_H_

//Project
#include "targets/msp430f5438a.h"


//Processor Selection                                                         (done this way to make project visually cleanest)
//#define   TARGET_SEL_CC2541                                                /* final target                                         */
#define     TARGET_SEL_MSP430F5438A                                          /* starting dev platform                                */
//#define   TARGET_SEL_MSP430F5529                                           /* shared dev example-platform                          */

//Globals
extern void mcu_init(void);
extern void mcu_enable_interrupts(void);
extern void mcu_demo(void);

#endif /* TARGETS_MCU_H_ */

