/************************************************************************************************************************************/
/** @file       radio.h
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
#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_

//Radios
#include "radios/cc1200_simple_link_reg_config.h"
#include "radios/cc1200.h"


//Project
#include "mcu.h"


//Globals
extern void radio_spi_init(void);
extern void radio_init(void);


#endif /* BSP_RADIO_H_ */

