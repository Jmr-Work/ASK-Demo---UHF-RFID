/************************************************************************************************************************************/
/** @file       mcu.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/19/17
 *  @last rev   6/19/17
 *
 *
 *  @notes      x
 *
 *  @section    Opens
 *          none current
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/

#include "mcu.h"


/************************************************************************************************************************************/
/** @fcn        void mcu_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void mcu_init(void) {

#ifdef TARGET_SEL_MSP430F5438A
    msp430f5438a_init();
#endif

    return;
}



/************************************************************************************************************************************/
/** @fcn        void mcu_enable_interrupts(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void mcu_enable_interrupts(void) {

#ifdef TARGET_SEL_MSP430F5438A
    msp430f5438a_enable_interrupts();
#endif


    return;
}


/************************************************************************************************************************************/
/** @fcn        void mcu_demo(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void mcu_demo(void) {

#ifdef TARGETS_MSP430F5438A_H_
    msp430f5438a_demo();
#endif

    return;
}

