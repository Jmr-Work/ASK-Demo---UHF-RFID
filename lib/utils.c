/************************************************************************************************************************************/
/** @file       x
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
#include "utils.h"


/************************************************************************************************************************************/
/** @fcn        void copy_mem(uint8_t *dest, uint8_t *src, uint32_t count)
 *  @brief      direct implementation of memcpy()
 *  @details    corrects hang bug observed with CC2541 & not understood
 *
 *  @param      [in] (uint8_t *) dest - destination
 *  @param      [in] (uint8_t *) src  - source
 *  @param      [in] (uint32_t) count - number of bytes to copy
 *
 *  @note       I have no idea why but memcpy causes spontaneous crashes, SOMETIMES... manual generation to solve this
 */
/************************************************************************************************************************************/
void copy_mem(uint8_t *dest, uint8_t *src, uint32_t count) {

    uint32_t i;

    for(i=0; i<count; i++) {
        dest[i] = src[i];
    }

    return;
}

