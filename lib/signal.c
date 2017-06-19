/************************************************************************************************************************************/
/** @file       signal.c
 *  @brief      x
 *  @details    x
 *
 *  @target     x
 *  @board      x
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    x
 *  @last rev   x
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
#include "signal.h"



SelectCommand sel_cmd = {
                        .command = 0b1010,
                        .target = 0b011,
                        .action = 0b000,
                        .membank = 0b01,
                        .pointer = 0b00000000,
                        .length = 0b00010000,
                        .mask = 0x0000,
                        .truncate = 0b0,
                        .crc16 = 0x0000
                        };

QueryCommand query_cmd = {
                          .command = 0b1000,
                               .dr = 0b0,
                                .m = 0b00,
                            .trext = 0b1,
                              .sel = 0b00,
                          .session = 0b11,
                           .target = 0b1,
                                .q = 0b0000,
                             .crc5 = 0b00000
                          };



/************************************************************************************************************************************/
/** @fcn        void signal_generate(void)
 *  @brief      generate the RFID signal for use in the project
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
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

    return;
}

