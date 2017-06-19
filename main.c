/************************************************************************************************************************************/
/** @file       main.c
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
#include "globals.h"




/************************************************************************************************************************************/
/** @fcn        int main(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
int main(void) {

    //Init
	sys_init();
	
	return EXIT_SUCCESS;
}


void sys_init(void) {

    //Watchodog
    WDTCTL = WDTPW | WDTHOLD;                                               /* Stop watchdog timer                                  */

    //MCU
    mcu_init();

    return;
}

