/************************************************************************************************************************************/
/** @file       cc1200.c
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
 *  @section    Points of Cautions
 *          The PA is observed to have ~18us ramp-on-time & ~28us ramp-off-time, ensure to account for this is signal design (e.g.
 *          enter & exit with 0xFF idle-high byte)
 *
 *  @section    Opens
 *          none current
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "cc1200.h"


/************************************************************************************************************************************/
/** @fcn        void cc1200_init(void)
 *  @brief      initialize the CC1200
 *  @details    x
 *
 *  @note    applies 1ms reset pulse to EMK
 *
 */
/************************************************************************************************************************************/
void cc1200_init(void) {

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
        for(;;);                                                           /* not the CC1200, spin                                  */
    }


    //******************************************************************************************************************************//
    // INIT RADIO CONFIG                                                                                                            //
    //******************************************************************************************************************************//
    cc12xx_configure();                                                     /* configure the radio for use                          */


    //******************************************************************************************************************************//
    // CALIBRATE                                                                                                                    //
    //******************************************************************************************************************************//
    trxSpiCmdStrobe(CC120X_SCAL);

    // Wait for calibration to be done (radio back in IDLE state)
    do {
      cc12xxSpiReadReg(CC120X_MARCSTATE, &marcState, 1);
    } while (marcState != 0x41);

    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC120X_SPWD);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_run_init(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1200_run_init(void) {

    //Empty FIFO before use (required)
    trxSpiCmdStrobe(CC120X_SFTX);

    // Strobe IDLE and fill TX FIFO
    trxSpiCmdStrobe(CC120X_SIDLE);

    // wait for radio to enter IDLE state
    while((trxSpiCmdStrobe(CC120X_SNOP)& 0xF0) != 0x00);
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_run_loop(void)
 *  @brief      x
 *
 *  @details    NUM_TXBYTES tracking example            (for illustration)
 *              pre              - NUM_TXBYTES = 0
 *              tx_buf write     - NUM_TXBYTES = 100
 *              send packet(STX) - NUM_TXBYTES = 100
 *              post 30k cycles  - NUM_TXBYTES = 78      (while(i--) {NOP})
 */
/************************************************************************************************************************************/
void cc1200_run_loop(void) {
    //Load the buffer into the TX_FIFO
    cc12xxSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                        /* Send the message                                     	*/

    // Send packet
    trxSpiCmdStrobe(CC120X_STX);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_run_waitForRoom(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1200_run_waitForRoom(void) {

    uint16_t open_ct;

    // Wait for radio to finish sending packet
    do {
        open_ct = cc12xx_queryTxFifo();

        asm(" NOP");

    } while(open_ct < 120);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_run_prepForNext(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1200_run_prepForNext(void) {
    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC120X_SPWD);

    return;
}

