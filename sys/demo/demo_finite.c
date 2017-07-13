/************************************************************************************************************************************/
/** @file       demo_finite.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    7/5/17
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
#include "demo_finite.h"


/************************************************************************************************************************************/
/** @fcn        void demo_finite(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Waveform (t=23.5ms)
 *      [0]: (13.4ms) CW
 *      [1]: (10.2ms) Off
 *
 *  @section    Opens
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void demo_finite(void) {

    uint16_t loop_ct = 0;
    uint16_t i = 0;

    uint8_t write_val;
    uint8_t fill_ct[4];

    volatile rfStatus_t      status;
    volatile rfStatus_fields statusFields;

    //----------------------Setup for Finite Mode (Mode Bit & Packet Length, that's it :) )-----------------------------------------//
    //PKT_CFG0
    write_val = 0x00;                                                       /* LENGTH_CONFIG(b7:b0) :  0b00, ELSE: 0                */
    cc12xxSpiWriteReg(CC120X_PKT_CFG0, &write_val, 1);

    //PKT_LEN
    write_val = 110;                                                        /* PACKET_LENGTH(b7:b0) : 100 (0xFF is max)             */
    cc12xxSpiWriteReg(CC120X_PKT_LEN, &write_val, 1);


    //------------------------------------Loop Finite Length Transmissions----------------------------------------------------------//
    for(;;) {
//!     P4OUT |= BIT7;                                                      /* BIT7 pulse: ?ms                                      */

        //Delay (makes scope easier read)
        for(i=42000; i>0; i--) {
            asm(" NOP");
        }

        //Load Buffer
        for(i=0; i<TX_BUFF_SIZE; i++) {
            tx_buff[i] = 0x55;                                              /* left here intentionally for future use if needed     */
        }

        //Transmit
        cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct[0], 1);               /* Grab FIFO Fill                                       */
        cc12xxSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                        /* Load the buffer into the TX_FIFO                     */
        cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct[1], 1);               /* Grab FIFO Fill                                       */
        trxSpiCmdStrobe(CC120X_STX);                                        /* Send packet                                          */
        cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct[2], 1);               /* Grab FIFO Fill                                       */

//!     P4OUT &= ~BIT7;

        //Wait for completion
        do {
            status = cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct[3], 1);

            statusFields = cc12xx_getRFStatusFields(status);

        } while(fill_ct[3] > 0);

        loop_ct++;
//!     P4OUT ^= BIT6;

        //Delay (makes scope easier read)
        for(i=4000; i>0; i--) {
            asm(" NOP");
        }

        //Flush the TX FIFO
        trxSpiCmdStrobe(CC120X_SFTX);                                       /* from IDLE state this is required                     */
    }
}

