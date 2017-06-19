/************************************************************************************************************************************/
/** @file       radio.c
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
#include "radio.h"




/************************************************************************************************************************************/
/** @fcn        void radio_spi_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void radio_spi_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    cc1200_spi_init();
#endif

    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void radio_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    cc1200_init();
#endif

    return;
}


