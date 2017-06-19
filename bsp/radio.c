/************************************************************************************************************************************/
/** @file       radio.c
 *  @brief      x
 *  @details    x
 *
 *  @target     x
 *  @board      x
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    x
 *  @last rev   x
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
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
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
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void radio_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    cc1200_init();
#endif

    return;
}


