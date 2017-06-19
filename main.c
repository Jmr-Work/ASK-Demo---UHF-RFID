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


uint8_t tx_buff[TX_BUFF_SIZE] = {0};

uint8_t data_arr[SRC_BUFF_SIZE] = {0x00};


/************************************************************************************************************************************/
/** @fcn        int main(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
int main(void) {

    //Init
	sys_init();
	
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

