/************************************************************************************************************************************/
/** @file       x
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
#include "rfid_test.h"


#include "../../lib/rfid.h"


/************************************************************************************************************************************/
/** @fcn        void rfid_test_chipSize(void)
 *  @brief      create waveform of 1ms Low, 16 Chips High, 1ms Low
 *  @details    simple code to test chip generation with oscilloscope
 *
 *  @post       waveform is generated for test in data_arr
 */
/************************************************************************************************************************************/
void rfid_test_chipSize(void) {
    for(;;);                                                                /* @open                                                */
//! uint32_t idle_cts = (88*NUM_BITS_IN_BYTE);                              /* 1ms of clock ticks @ 16 MHz                          */

//! dataBitGenLoc loc = {0, 0};

//! loc = rfid_sig_idleRF(data_arr, loc, idle_cts, false);

//! loc = rfid_sig_idleRF(data_arr, loc, 16, true);

//! loc = rfid_sig_idleRF(data_arr, loc, idle_cts, false);

    //Store new signal size
//! signal_size = loc.arr_ind+1;                                            /* e.g. if 3 bytes in array, arr_ind=2, signal_size = 3 */

//! return;
}


/************************************************************************************************************************************/
/** @fcn        void rfid_test_EOS(void)
 *  @brief      confirm operation of rfid_sig_endOfSignal()
 *  @details    by debug inspection, not OTA
 *
 *  @note       confirm does not overwrite outside it's access scope
 */
/************************************************************************************************************************************/
void rfid_test_EOS(void) {

    int i;
    bool cw_on;

    //Run as H, then as L
    for(i=0; i<2; i++) {

        cw_on = (i==0);

        dataBitGenLoc loc = {0, 0};

        //-----------------------------------------------Test b0:b3 L---------------------------------------------------------------//
        data_arr[0] = 0x00;                                                 /* none                                                 */

        loc.arr_ind = 0;
        loc.byte_ind = 4;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);


        //-----------------------------------------------Test b0 L, b1 H, b3 H------------------------------------------------------//
        data_arr[4] = BIT1|BIT3;                                            /* b1b3 H                                               */

        loc.arr_ind = 4;
        loc.byte_ind = 4;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);


        //-----------------------------------------------Test b0 H, b5 H, b6 L------------------------------------------------------//
        data_arr[12] = BIT0|BIT5;                                           /* b3b5 H                                               */

        loc.arr_ind = 12;
        loc.byte_ind = 7;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);


        //-----------------------------------------------Test b0:b4 L, b5 H---------------------------------------------------------//
        data_arr[100] = BIT5;                                               /* b5 H                                                 */

        loc.arr_ind = 100;
        loc.byte_ind = 6;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);


        //-----------------------------------------------Test Full Byte-------------------------------------------------------------//
        data_arr[7] = 0xEE;                                                 /* 0xEE                                                 */

        loc.arr_ind = 7;
        loc.byte_ind = 0;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);


        //-----------------------------------------------Test Empty Byte------------------------------------------------------------//
        data_arr[14] = 0x00;                                                /* 0xEE                                                 */

        loc.arr_ind = 14;
        loc.byte_ind = 0;

        rfid_sig_endOfSignal(data_arr, loc, cw_on);

    }


    return;
}

