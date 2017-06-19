/************************************************************************************************************************************/
/** @file       timers.c
 *  @brief      Clocks and GPIO set-up would be here and are in the example, but have not been shown to reduce the code size
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/19/17
 *  @last rev   6/19/17
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
#include "timers.h"


/************************************************************************************************************************************/
/** @fcn        void timers_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void timers_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    msp430f5438a_timers_init();
#endif

    return;
}


#ifdef TARGET_IS_MSP430F5438A
/************************************************************************************************************************************/
/** @fcn        __interrupt void Timer0_A0 (void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void) {

    P4OUT ^= BIT0;

    return;
}
#endif

