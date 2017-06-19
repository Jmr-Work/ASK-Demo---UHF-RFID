#ifndef BSP_MCU_H_
#define BSP_MCU_H_

//Project
//#include "targets/msp430f5438a/msp430f5438a.h"


//Processor Selection                                                         (done this way to make project visually cleanest)
//#define   TARGET_IS_CC2541                                                /* final target                                         */
//#define   TARGET_IS_MSP430F5438A                                          /* starting dev platform                                */
//#define   TARGET_IS_MSP430F5529                                           /* shared dev example-platform                          */

//Globals
extern void mcu_init(void);
//extern void mcu_enable_interrupts(void);
//extern void mcu_demo(void);


#endif /* BSP_MCU_H_ */

