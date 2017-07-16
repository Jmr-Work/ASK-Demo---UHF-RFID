/************************************************************************************************************************************/
/** @file       demo_cont.c
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
#include "demo_cont.h"


/************************************************************************************************************************************/
/** @fcn        void demo_cont(void)
 *  @brief      Continuous-Tx mode, with static buffer contents
 *  @details    x
 */
/************************************************************************************************************************************/
void demo_cont(void) {

    uint16_t loop_ct = 0, i = 0;

    //Generate Waveform

    //All Empty
    for(i=0; i< TX_BUFF_SIZE; i++) {
        tx_buff[i] = 0x00;
    }

    //Add 25% Pulse (of bits)
    for(i=0; i< TX_BUFF_SIZE/4; i++) {
        tx_buff[i] = 0x55;
    }

    //First Char holds 4 chips-low
    tx_buff[0] = b11000011;

    //Second Char all high
    tx_buff[1] = b11111111;

    //Third char two low
    tx_buff[2] = b11100111;


    //------------------------------------------------Send Waveform-----------------------------------------------------------------//
    radio_cont_run_init();

    for(;;) {
        radio_cont_run_loop();

        radio_run_waitForRoom();

        radio_run_prepForNext();

        loop_ct++;
    } /* end for(;;)            */
}

