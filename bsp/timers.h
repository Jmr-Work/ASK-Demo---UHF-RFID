/************************************************************************************************************************************/
/** @file       timers.h
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    x
 *  @last rev   x
 *
 *  @src  http://coder-tronics.com/msp430-timer-pwm-tutorial/

 *
 *  @section     Opens
 *      Determine more precisely what the clock source & rate is. This is functional, but the clock sourcing is unknown!
 *
 *  @notes      x
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#ifndef BSP_TIMERS_H_
#define BSP_TIMERS_H_

//Libraries
#include <stdint.h>

//Processor
#include <msp430.h>

//Project
#include "mcu.h"

//Globals
extern void timers_init(void);


#endif /* BSP_TIMERS_H_ */
