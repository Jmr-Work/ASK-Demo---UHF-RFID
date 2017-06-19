/************************************************************************************************************************************/
/** @file       rfid.c
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
 *  @brief  making signal generation easy, procedural and quick
 *          - inputs (*arr, arr_ind to write to)
 *          - outputs (new_arr_int of next free write location
 *          - assum  (Delim: 1ch, PW: 1ch, Data0: 2ch, Data1: 3ch, RTCal: 6, TRCal: 17) *see 'ISO 18000-6C Gen Notes.xlsx'
 *          - assume (will always be passed valid array to write to
 *          - sections supported: Idle_RF, Off, Select, Query
 *
 *  @notes
 *          - write 8 symbols per byte
 *          - first byte of transmission is [0]
 *          - first bit of transmission is b0?
 *
 *  @section    Opens
 *          none current
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "rfid.h"


/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_Query(uint8_t arr[], dataBitGenLoc loc, QueryCommand cmd)
 *  @brief      x
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
 *      calculate & insert valid CRC-5
 *      confirm this matches what a reader outputs
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Generation Format
 *      - Preamble -  Delim, Data-0, RTCal, TRCal (PDF p.165)
 *      - Databits (PDF p.201)
 *      - EOS (high)
 *
 *  @section    CRC-5
 *      Poly: x^5 + x^3 + 1         ([1] Sec 6.5.7.2 - p.26/48)
 *
 *  @note       Query - [1] Sec 9.3.2.11.2.1 - p.179 (PDF p.201)
 */
/************************************************************************************************************************************/
dataBitGenLoc rfid_sig_Query(uint8_t arr[], dataBitGenLoc loc, QueryCommand cmd) {

    //Pre-amble
    loc = rfid_sig_delim(arr, loc);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_RTCal(arr, loc);
    loc = rfid_sig_TRCal(arr, loc);


    //Command (4b) - 0b1000
    loc = rfid_sig_dataBit(arr, loc, true);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //DR (1b) - 0b0
    loc = rfid_sig_dataBit(arr, loc, false);

    //M (2b) - 0b00
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //TRext (1b) - -b1
    loc = rfid_sig_dataBit(arr, loc, true);

    //Sel (2b) - 0b00
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Session (2b) - 0b11
    loc = rfid_sig_dataBit(arr, loc, true);
    loc = rfid_sig_dataBit(arr, loc, true);

    //Target (1b) - 0b1
    loc = rfid_sig_dataBit(arr, loc, true);

    //Q (4b) - 0b0000
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //CRC-5 (5b) - 0bxxxx
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    return loc;
}



/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_Select(uint8_t arr[], dataBitGenLoc loc, SelectCommand cmd)
 *  @brief      x
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
 *      calculate & insert valid CRC-16
 *      confirm this matches what a reader outputs
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
 *  @note       Select - [1] Sec 9.3.2.11.1.1 - p.177 (PDF p.199)
 */
/************************************************************************************************************************************/
dataBitGenLoc rfid_sig_Select(uint8_t arr[], dataBitGenLoc loc, SelectCommand cmd) {


    //Command (4b) - 0b1010
    loc = rfid_sig_dataBit(arr, loc, true);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, true);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Target - 0b011
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Action - 0b000
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Membank - 0b01
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Pointer - 0b00000000
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Length - 0b00010000
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Mask - 0bxxxxxxxxxxxxxxxx
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    //Truncate - 0b0
    loc = rfid_sig_dataBit(arr, loc, false);

    //CRC-16 - 0bxxxxxxxxxxxxxxxx
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);
    loc = rfid_sig_dataBit(arr, loc, false);

    return loc;
}


/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_idleRF(uint8_t *arr, dataBitGenLoc loc, uint32_t idleRF_cts, bool cw_on)
 *  @brief      x
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
dataBitGenLoc rfid_sig_idleRF(uint8_t *arr, dataBitGenLoc loc, uint32_t idleRF_cts, bool cw_on) {

    while(idleRF_cts--) {
        //add the bit
        if(cw_on) {
            arr[loc.arr_ind] |= (1<<loc.byte_ind);
        } else {
            arr[loc.arr_ind] &= ~(1<<loc.byte_ind);
        }

        //update the loc for next
        if(++loc.byte_ind >= BITS_IN_BYTE) {
            loc.byte_ind = 0;
            loc.arr_ind++;
        }
    }

    return (loc);
}



/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_dataBit(uint8_t arr[], dataBitGenLoc loc, bool bitVal)
 *  @brief      x
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
dataBitGenLoc rfid_sig_dataBit(uint8_t arr[], dataBitGenLoc loc, bool bitVal) {

    uint32_t arr_ind  = loc.arr_ind;
    uint32_t byte_ind = loc.byte_ind;

    //Data1(3 High, 1 Low)
    //Data0(2 High, 1 Low)

    if(bitVal) {
        //CHIP1 (H)
        arr[arr_ind] |= (1<<byte_ind);
        byte_ind = (byte_ind+1) % BITS_IN_BYTE;

        if(byte_ind == 0) {
            arr_ind++;
        }
    }

    //CHIP2 (H)
    arr[arr_ind] |= (1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    //CHIP3 (H)
    arr[arr_ind] |= (1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    //CHIP4 (L)
    arr[arr_ind] &= ~(1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    dataBitGenLoc newLoc;

    newLoc.arr_ind = arr_ind;
    newLoc.byte_ind = byte_ind;

    return newLoc;
}


/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_delim(uint8_t *arr, dataBitGenLoc loc)
 *  @brief      x
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
dataBitGenLoc rfid_sig_delim(uint8_t *arr, dataBitGenLoc loc) {

    uint32_t arr_ind  = loc.arr_ind;
    uint32_t byte_ind = loc.byte_ind;

    //Low (1 Symbol, PW)
    arr[arr_ind] &= ~(1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    dataBitGenLoc newLoc;

    newLoc.arr_ind = arr_ind;
    newLoc.byte_ind = byte_ind;

    return newLoc;
}



/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_RTCal(uint8_t arr[], dataBitGenLoc loc)
 *  @brief      x
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
dataBitGenLoc rfid_sig_RTCal(uint8_t arr[], dataBitGenLoc loc) {

    uint32_t i;
    uint32_t arr_ind  = loc.arr_ind;
    uint32_t byte_ind = loc.byte_ind;

    //High (5 Symbols)
    for(i=0; i<5; i++) {
        arr[arr_ind] |= (1<<byte_ind);
        byte_ind = (byte_ind+1) % BITS_IN_BYTE;

        if(byte_ind == 0) {
            arr_ind++;
        }
    }


    //Low (1 Symbol, PW)
    arr[arr_ind] &= ~(1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    dataBitGenLoc newLoc;

    newLoc.arr_ind = arr_ind;
    newLoc.byte_ind = byte_ind;

    return newLoc;
}



/************************************************************************************************************************************/
/** @fcn        dataBitGenLoc rfid_sig_TRCal(uint8_t arr[], dataBitGenLoc loc)
 *  @brief      x
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
dataBitGenLoc rfid_sig_TRCal(uint8_t arr[], dataBitGenLoc loc) {

    uint32_t i;
    uint32_t arr_ind  = loc.arr_ind;
    uint32_t byte_ind = loc.byte_ind;

    //High (16 Symbols)
    for(i=0; i<16; i++) {
        arr[arr_ind] |= (1<<byte_ind);
        byte_ind = (byte_ind+1) % BITS_IN_BYTE;

        if(byte_ind == 0) {
            arr_ind++;
        }
    }


    //Low (1 Symbol, PW)
    arr[arr_ind] &= ~(1<<byte_ind);
    byte_ind = (byte_ind+1) % BITS_IN_BYTE;

    if(byte_ind == 0) {
        arr_ind++;
    }

    dataBitGenLoc newLoc;

    newLoc.arr_ind = arr_ind;
    newLoc.byte_ind = byte_ind;

    return newLoc;
}

