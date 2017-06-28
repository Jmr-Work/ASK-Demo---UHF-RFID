/************************************************************************************************************************************/
/** @file       cc1175.c
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
#include "cc1175.h"


/************************************************************************************************************************************/
/** @fcn        void cc1175_init(void)
 *  @brief      initialize the CC1175
 *  @details    x
 *
 *  @note    applies 1ms reset pulse to EMK
 *
 */
/************************************************************************************************************************************/
void cc1175_init(void) {

    uint8_t  marcState;


    //******************************************************************************************************************************//
    //                                                          RESET                                                               //
    //******************************************************************************************************************************//
    //Hardware
    mcu_radio_hw_reset();

    //Software
    mcu_radio_sw_reset();

    //Verify ID
    bool valid_id = cc12xx_verifyPartNumber();

    if(!valid_id) {
		for(;;);                                                            /* not the CC1175, spin                                 */
    }


    //******************************************************************************************************************************//
    // INIT RADIO CONFIG                                                                                                            //
    //******************************************************************************************************************************//
    cc12xx_configure();                                                     /* configure the radio for use                          */


    //******************************************************************************************************************************//
    // CALIBRATE                                                                                                                    //
    //******************************************************************************************************************************//
    trxSpiCmdStrobe(CC112X_SCAL);                                           /* CC1200 - CC120X_SCAL                                 */

    // Wait for calibration to be done (radio back in IDLE state)
    do {
      cc12xxSpiReadReg(CC112X_MARCSTATE, &marcState, 1);                    /* CC1200 - CC120X_MARCSTATE                            */
    } while (marcState != 0x41);

    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC112X_SPWD);                                           /* CC1200 - CC120X_SPWD                                 */

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_init(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_init(void) {

    //Empty FIFO before use (required)
    trxSpiCmdStrobe(CC112X_SFTX);                                           /* CC1200 - CC120X_SFTX                                 */

    // Strobe IDLE and fill TX FIFO
    trxSpiCmdStrobe(CC112X_SIDLE);                                          /* CC1200 - CC120X_SIDLE                                */

    // wait for radio to enter IDLE state
    while((trxSpiCmdStrobe(CC112X_SNOP)& 0xF0) != 0x00);                    /* CC1200 - CC120X_SNOP                                 */

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_loop(void) {

    //Load the buffer into the TX_FIFO
    cc112xSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                            /* Send the message                                     */

    // Send packet
    trxSpiCmdStrobe(CC112X_STX);                                            /* CC1200 - CC120X_STX                                  */

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_waitForRoom(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_waitForRoom(void) {

    uint16_t open_ct;

    // Wait for radio to finish sending packet
    do {
        open_ct = cc12xx_queryTxFifo();

        asm(" NOP");

    } while(open_ct < 120);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_prepForNext(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_prepForNext(void) {

    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC112X_SPWD);                                           /* CC1200 - CC120X_SPWD                                 */

    return;
}

