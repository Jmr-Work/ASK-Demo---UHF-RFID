/************************************************************************************************************************************/
/** @file		demo_rfid.c
 * 	@brief		RFID Signal Generation Demo, Finite Mode
 * 	@details	x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/19/17
 *  @last rev   6/19/17
 *
 *
 * 	@notes		x
 *
 * 	@section	Opens
 * 			none current
 *
 * 	@section	Legal Disclaimer
 * 			All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 * 			Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "demo_rfid.h"


//Locals
static void gen_signal(void);


/************************************************************************************************************************************/
/**	@fcn		void demo_rfid(void)
 *  @brief		x
 *  @details	x
 */
/************************************************************************************************************************************/
void demo_rfid(void) {

    uint32_t i, loop_ct = 0;                                                   /* number of cycles through the loop                 */
    uint8_t fill_ct, write_val;

    volatile rfStatus_t      status;
    volatile rfStatus_fields statusFields;

    //Init
    gen_signal();
    for(i=0;i<TX_BUFF_SIZE;i++) { tx_buff[i] = 0x55; }                          /* temp...                                          */


    //----------------------Setup for Finite Mode (Mode Bit & Packet Length, that's it :) )-----------------------------------------//
    //PKT_CFG0
    write_val = 0x00;                                                       /* LENGTH_CONFIG(b7:b0) :  0b00, ELSE: 0                */
    cc12xxSpiWriteReg(CC120X_PKT_CFG0, &write_val, 1);

    //PKT_LEN
    write_val = 110;                                                        /* PACKET_LENGTH(b7:b0) : 100 (0xFF is max)             */
    cc12xxSpiWriteReg(CC120X_PKT_LEN, &write_val, 1);


    for(;;) {

        //transmit
        cc12xxSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                        /* Load the buffer into the TX_FIFO                     */
        trxSpiCmdStrobe(CC120X_STX);                                        /* Send packet                                          */

        //wait for completion
        do {
            status = cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct, 1);
            statusFields = cc12xx_getRFStatusFields(status);
        } while(fill_ct> 0);

        //Delay (makes scope easier read)
        for(i=4000; i>0; i--) { asm(" NOP"); }

        //Flush the TX FIFO
        trxSpiCmdStrobe(CC120X_SFTX);                                       /* from IDLE state this is required                     */

        //Repeat
        loop_ct++;
    }
}


/************************************************************************************************************************************/
/** @fcn        static void gen_signal(void)
 *  @brief      generate the signal for transmission
 *  @details    a static signal, with design for potential final use on wallet
 *
 *  @section    Reference
 *      [2] - Link Timing:9  -  R=>T preamble and frame-sync
 *      [2] - Link Timing:17 -  Command Durations
 *
 *  @section    Signal
 *      Idle-High (725us)
 *      Select    (3162.5us)
 *      Idle-High (725us)
 *      Query     (1425us)
 *      Idle-High (725us)
 *      Idle-Low  (3237.5s)  <- remainder of buffer (10ms - 725x3 - 3162.5 - 1425)
 *
 *  @post   buffer is completely full with signal to Tx on Finite Mode
 */
/************************************************************************************************************************************/
static void gen_signal(void) {

    //(all to buff, fill)

    //gen Select, with Idle-High (725us) lead_time

    //gen Query, with Idle-High (725us) lead_time, Idle-High (725us) exit_time, Idle-Low (3237.5us) post_time

    return;
}
