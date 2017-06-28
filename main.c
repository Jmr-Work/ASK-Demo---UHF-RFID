/************************************************************************************************************************************/
/** @file       main.c
 *  @brief      illustration & demo of using the cc12xx for UHF-RFID ASK Generation
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/19/17
 *  @last rev   6/19/17
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
 *      [1] - ISO/IEC 18000-6:C, Second Edition
 *      [2] - ISO 18000-6C Gen Notes
 *      [3] - CC1175 Datasheet
 *      [4] - CC1175 User's Guide
 *      [5] - CC1200 Datasheet
 *      [6] - CC1200 User's Guide
 *      [7] - CC1175 EMK Design Files
 *      [8] - CC1200 EMK Design Files
 *
 *  @section    Opens
 *          deprecate temp_radio.h                          (correct header format in consideration)
 *          cleanup cc12xx.h header '<TEMP>' section
 *          validate packet contents
 *          validate symbol timing
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
}


/************************************************************************************************************************************/
/** @fcn        void sys_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void sys_init(void) {

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

