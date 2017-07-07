/************************************************************************************************************************************/
/** @file       demo_register.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    7/5/17
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
#include "demo_register.h"


/************************************************************************************************************************************/
/** @fcn        void demo_register(void)
 *  @brief      x
 *  @details    x
 *
 *  @pre        cc12xx radio initialized & ready for use
 *
 *  @section    Opens
 *      make this fancier... more reg reads!
 */
/************************************************************************************************************************************/
void demo_register(void) {

    uint8_t partnum_reg;

    //-------------------------------------------------Loop Register Reads----------------------------------------------------------//
    for(;;) {

        //Read the part number
        cc12xxSpiReadReg(CC120X_PARTNUMBER, (uint8_t *) &partnum_reg, 1);

        partnum_reg = 0x00;                                                 /* reset, and read again!                               */
    }
}

