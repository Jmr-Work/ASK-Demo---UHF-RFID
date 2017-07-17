/************************************************************************************************************************************/
/** @file       demo_rfid.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    7/17/17
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
#include "demo_rfid.h"


/************************************************************************************************************************************/
/** @fcn        void demo_rfid(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Waveform (t=23.5ms)
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void demo_rfid(void) {

    uint16_t loop_ct = 0;

    uint8_t write_val;
    uint8_t fill_ct[4];

    volatile rfStatus_t      status;
    volatile rfStatus_fields statusFields;

    //----------------------Setup for Finite Mode (Mode Bit & Packet Length, that's it :) )-----------------------------------------//
    //PKT_CFG0
    write_val = 0x00;                                                       /* LENGTH_CONFIG(b7:b0) :  0b00, ELSE: 0                */
    cc12xxSpiWriteReg(CC12XX_PKT_CFG0, &write_val, 1);

    //PKT_LEN
    write_val = TX_BUFF_SIZE;                                               /* PACKET_LENGTH(b7:b0) : 100 (0xFF is max)             */
    cc12xxSpiWriteReg(CC12XX_PKT_LEN, &write_val, 1);

    //Init Signal
    signal_generate();

    //------------------------------------Loop Finite Length Transmissions----------------------------------------------------------//
    for(;;) {
        signal_grab_next();

        //Transmit
        cc12xxSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                        /* Load the buffer into the TX_FIFO                     */
        trxSpiCmdStrobe(CC12XX_STX);                                        /* Send packet                                          */

        //Wait for completion
        do {
            status = cc12xxSpiReadReg(CC12XX_NUM_TXBYTES, &fill_ct[3], 1);
            statusFields = cc12xx_getRFStatusFields(status);
        } while(fill_ct[3] > 0);

        //Post
        loop_ct++;
        delay(4000);                                                        /* Delay (makes scope easier read)                      */

        //Flush the TX FIFO
        trxSpiCmdStrobe(CC12XX_SFTX);                                       /* from IDLE state this is required                     */
    }
}



/************************************************************************************************************************************/
/** @fcn        static void delay(uint32_t cts)
 *  @brief      general-purpose delay loop
 *  @details    x
 *
 *  @param      [in] (uint32_t) cts - number of counts to delay
 */
/************************************************************************************************************************************/
static void delay(uint32_t cts) {

    uint32_t i;

    for(i=cts; i>0; i--) {
        asm(" NOP");
    }

    return;
}
