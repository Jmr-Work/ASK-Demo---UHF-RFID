/************************************************************************************************************************************/
/** @file       main.c
 *  @brief      illustration & demo of using the cc12xx for UHF-RFID ASK Generation
 *  @details    x
 *
 *  @target     MSP430F5438A
 *  @board      TrxEB
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    x
 *  @last rev   x
 *
 *  @section    Output Targets
 *      Tari = 25us
 *      LF   = 40 kHz (min)
 *      Mod  = FM0
 *      DR   = 8
 *
 *  @section    Development Procedure
 *      develop reg api & lib
 *
 *  @section    References
 *      1 - ISO/IEC 18000-6:C, Second Edition
 *      2 - ISO 18000-6C Gen Notes.xlsx (see doc/)
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
 *
 *  @section    Waveform
 *      Pre: .        Idle-Off    []
 *      [0]: (200 us) Idle-CW    [200us]
 *      [1]: .        Select      [3162.5us]
 *      [2]: (200 us) Idle-CW     [200us]
 *      [3]: .        Query       [1425us]
 *      [4]: (400 ms) Idle-CW     [400us]
 *      [5]: .        Idle-Off    [1000us]
 */
/************************************************************************************************************************************/
int main(void) {

    //Init
	sys_init();
	
	//Generate Waveform
//!	//<open>

	//Run Demo
	mcu_demo();

	return EXIT_SUCCESS;
}


/************************************************************************************************************************************/
/** @fcn        void sys_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void sys_init(void) {

    //Watchodog
    WDTCTL = WDTPW | WDTHOLD;                                               /* Stop watchdog timer                                  */

    //MCU
    mcu_init();

    //Clocks
    clocks_init();

    //GPIO
    gpio_init();

    //Periphs
    timers_init();
    radio_spi_init();

    //Board
    radio_init();

    //Begin Operations
    mcu_enable_interrupts();

    return;
}

