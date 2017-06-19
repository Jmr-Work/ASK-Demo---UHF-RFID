/************************************************************************************************************************************/
/** @file       msp430f5438a_demo.c
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
#include "msp430f5438a_demo.h"


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_demo(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Waveform (see signal.c:signal_generate()
 *      Pre: .        Idle-Off    []
 *      [0]: (200 us) Idle-CW     [200us]
 *      [1]: .        Select      [3162.5us]
 *      [2]: (200 us) Idle-CW     [200us]
 *      [3]: .        Query       [1425us]
 *      [4]: (400 ms) Idle-CW     [400us]
 *      [5]: .        Idle-Off    [1000us]
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void msp430f5438a_demo(void) {

    uint16_t loop_ct = 0;
    uint16_t open_ct = 0;

    //Generate Waveform
    signal_generate();
    signal_grab_next();

    //Empty FIFO before use (required)
    trxSpiCmdStrobe(CC120X_SFTX);

    // Strobe IDLE and fill TX FIFO
    trxSpiCmdStrobe(CC120X_SIDLE);

    // wait for radio to enter IDLE state
    while((trxSpiCmdStrobe(CC120X_SNOP)& 0xF0) != 0x00);

    for(;;) {

        P4OUT |= BIT7;                                                      /* BIT7 pulse: 101ms                                    */

        //Load the buffer into the TX_FIFO
        cc112xSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                        /* Send the message                                     */

        // Send packet
        trxSpiCmdStrobe(CC120X_STX);

        signal_grab_next();

        // Wait for radio to finish sending packet
        do {
            open_ct = cc1200_queryTxFifo();

            asm(" NOP");

        } while(open_ct < 120);

        P4OUT &= ~BIT7;

        // Put radio in powerdown to save power
        trxSpiCmdStrobe(CC120X_SPWD);

        loop_ct++;

        P4OUT ^= BIT6;
    } /* end for(;;)    */
}

