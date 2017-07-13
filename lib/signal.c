/************************************************************************************************************************************/
/** @file       signal.c
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
 *  @assum      signal stored is always stored to the full byte on signal completion (e.g. if your message is 4 bits, toss into b0:b3
 *              then leave b4:b7 High!)
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "signal.h"


SelectCommand sel_cmd = {
                        .command  = b1010,
                        .target   = b011,
                        .action   = b000,
                        .membank  = b01,
                        .pointer  = b00000000,
                        .length   = b00010000,
                        .mask     = 0x0000,
                        .truncate = b0,
                        .crc16    = 0x0000
                        };

QueryCommand query_cmd = {
                          .command = b1000,
                               .dr = b0,
                                .m = b00,
                            .trext = b1,
                              .sel = b00,
                          .session = b11,
                           .target = b1,
                                .q = b0000,
                             .crc5 = b00000
                          };

//Signal Vars
uint16_t next_grab_ind = 0;                                                 /* where to grab for the next transmission segment      */
uint16_t signal_size;                                                       /* how big the signal stored is, measured in bytes      */


/************************************************************************************************************************************/
/** @fcn        void signal_generate(void)
 *  @brief      generate the RFID signal for use in the project
 *  @details    x
 *
 *  @post       data is generated from [0]:b0..[signal_size-1]:b7
 *
 *  @note       this generation concludes on Idle-Low, violating our 'thou shalt leave on HIGH' edict, but this is intentional!
 */
/************************************************************************************************************************************/
void signal_generate(void) {

    dataBitGenLoc loc = {0,0};                                              /* address used in calc for signal                      */

    //Generate Waveform (@note  1600 counts per 100us w/FCPU=16MHz)
    loc = rfid_sig_idleRF(data_arr, loc, 3200, true);

    loc = rfid_sig_Select(data_arr, loc, sel_cmd);

    loc = rfid_sig_idleRF(data_arr, loc, 3200, true);

    loc = rfid_sig_Query(data_arr, loc, query_cmd);

    loc = rfid_sig_idleRF(data_arr, loc, 6400, true);

    loc = rfid_sig_idleRF(data_arr, loc, 3200, false);

    //Store new signal size
    signal_size = loc.arr_ind+1;                                            /* e.g. if 3 bytes in array, arr_ind=2, signal_size = 3 */

    return;
}


/************************************************************************************************************************************/
/** @fcn        void signal_grab_next(void)
 *  @brief      grab next tx buffer segment
 *  @details    x
 *
 *  @section    Opens
 *      re-enable memcpy (jmr disabled to meet free license compile restrictions)
 */
/************************************************************************************************************************************/
void signal_grab_next(void) {

//! memcpy(&tx_buff[0], &data_arr[next_grab_ind], TX_BUFF_SIZE*sizeof(uint8_t));      /* @open   validate in depth                  */

//! next_grab_ind = (next_grab_ind + TX_BUFF_SIZE) % signal_size;
    
    uint16_t i;
  
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
    
    //Thirdchar two low
    tx_buff[2] = b11100111;

    
    return;
}

