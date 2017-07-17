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
 *  @section    Vocabulary
 *      Waveform - the full signal defined for transmission (msg[], idle_durations, type)
 *      Slice    - a component of waveform loaded into the Tx buffer. Size defined by tx_buff size
 *      Active   - the slice currently in generation
 *      Chip     - TX FIFO smallest component (i.e. a bit in FIFO)
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
  

//Transmit Waveform
Waveform wvfm;                                                            /* the meat, this is where the message goes!            */


/************************************************************************************************************************************/
/**! @fcn        void signal_generate(void)
 *!  @brief      generate the RFID signal for use in the project
 *!  @details    x
 *
 *   @post       waveform is ready for use by transmit library
 *
 *   @section   Message Contents
 *      Idle-High   150 us
 *      Select
 *      Idle-High   725 us
 *      Query
 *      Idle-High   150 us
 *      Idle-Low    2.0 ms
 *
 *   @section   Opens
 *      Generate contents of q & s
 *      specify correct timing values
 *      generate routines to calculate CRC5 & CRC16
 */
/************************************************************************************************************************************/
void signal_generate(void) {


#ifdef DEMO_SEL_RFID
    uint32_t s_times[3] = {NUM_CHIPS_IN_725_US, 0, 0};
    uint32_t q_times[3] = {NUM_CHIPS_IN_725_US, NUM_CHIPS_IN_725_US, NUM_CHIPS_IN_725_US};

    volatile QueryCommand q = {
        .command = b1000,
        .dr      = b0,
        .m       = b00,
        .trext   = b1,
        .sel     = b00,
        .session = b11,
        .target  = b1,
        .q       = b0000,
        .crc5    = 0x00                                                     /* @open    calculate value at runtime                  */
    };

    volatile SelectCommand s = {
        .command  = b1010,
        .target   = b011,
        .action   = b000,
        .membank  = b01,
        .pointer  = b00000000,
        .length   = b00010000,
        .mask     = b00000000,                                              /* @open    gen val                                     */
        .truncate = b0,
        .crc16    = 0x0000                                                  /* @open    calculate value at runtime                  */
    };

    //Add Select
    load_command(SELECT, (uint8_t *) &s, s_times);

    //Add Query
    load_command(QUERY, (uint8_t *) &q, q_times);

    //Set Mode (continuous)
    wvfm.mode = true;

#else
    for(;;);                                                                /* @open!                                               */
#endif


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
    for(;;);                                                                /* @open                                                */
//    memcpy(&tx_buff[0], &data_arr[next_grab_ind], TX_BUFF_SIZE*sizeof(uint8_t));    /* @open   validate in depth                  */
//
//    next_grab_ind = (next_grab_ind + TX_BUFF_SIZE) % signal_size;
//
//    uint16_t i;
//
//    //All Empty
//    for(i=0; i< TX_BUFF_SIZE; i++) {
//        tx_buff[i] = 0x00;
//    }
//
//    //Add 25% Pulse (of bits)
//    for(i=0; i< TX_BUFF_SIZE/4; i++) {
//        tx_buff[i] = 0x55;
//    }
//
//    //First Char holds 4 chips-low
//    tx_buff[0] = b11000011;
//
//    //Second Char all high
//    tx_buff[1] = b11111111;
//
//    //Thirdchar two low
//    tx_buff[2] = b11100111;
//
//
//    return;
}




/************************************************************************************************************************************/
/** @fcn        static void load_command(Command type, uint8_t *cmd, uint32_t *idle_cts)
 *  @brief      load a message into the buffer
 *  @details    x
 *
 *  @param      [in] (Command) type - Type of RFID message (e.g. 'QUERY')
 *  @param      [in] (uint8_t *) cmd - message contents
 *                      *ptr to QueryCommand, SelectCommand, etc.
 *  @param      [in] (uint32_t *) idle_cts - array of idle counts to use for message
 *                      [0] - pre_idle_high_ct
 *                      [1] - post_idle_high_ct
 *                      [2] - exit_idle_low_ct
 *
 *  @section    Opens
 *      validate this works!
 *
 *  @assum      waveform has free space for storage
 *
 *  @note       kept static for now to minimize footprint
 */
/************************************************************************************************************************************/
static void load_command(Command type, uint8_t *cmd, uint32_t *idle_cts) {

    uint32_t size;

    switch(type) {
    case QUERY:
        size = sizeof(QueryCommand);
        break;
    case SELECT:
        size = sizeof(SelectCommand);
        break;
    }

    //Grab msg ptr
    uint8_t index = wvfm.msg_count;                                         /* e.g. if there are 4 items in array, X[4] is next loc */
    Message *msg = &wvfm.msgs[index];                                       /* where to load the new command                        */

    //Store the command type
    msg->type = (uint8_t) type;

    //Store the timing values
    msg->pre_idle_high_ct  = idle_cts[0];
    msg->post_idle_high_ct = idle_cts[1];
    msg->exit_idle_low_ct  = idle_cts[2];

    //Store the message
    copy_mem((uint8_t *) &msg->data, cmd, size);

    //******************************************************************************************************************************//
    //                                      CALCULATED VARS (TIME VALS - START/DUR/END)                                             //
    //******************************************************************************************************************************//
    Message *last_msg;

    //Start
    if(!wvfm.msg_count) {
        msg->t_start = 0;                                                   /* '0' if at front                                      */
    } else {
        last_msg = &wvfm.msgs[wvfm.msg_count];                              /* 'last end' else                                      */
        msg->t_start  = last_msg->t_end;
    }

    //Duration
    msg->t_dur = calc_msg_duration(type, cmd);

    //End
    msg->t_end = msg->t_start + msg->t_dur;

    //Update storage index
    wvfm.msg_count++;

    return;
}


/************************************************************************************************************************************/
/** @fcn        uint32_t calc_msg_duration(Command type, uint8_t *cmd)
 *  @brief      calculate how many chips will be in the message
 *  @details    x
 *
 *  @section    Purpose
 *      for use in timing calcs by app
 *
 *  @param      [in] (Command) type - type of RFID command (e.g. 'QUERY')
 *  @param      [in] (uint8_t *) cmd - message contents
 *                      *ptr to QueryCommand, SelectCommand, etc.
 *
 *  @return (uint32_t) time of command (Chips)
 *
 *  @assum  Tari = 25us
 *
 *  @section    Opens
 *      test & validate
 */
/************************************************************************************************************************************/
uint32_t calc_msg_duration(Command type, uint8_t *cmd) {

    uint32_t cmd_dur_cts = 0;
    uint32_t d0_ct = 0;
    uint32_t d1_ct = 0;
    uint16_t i, j;


    //******************************************************************************************************************************//
    //                                                      HEADER                                                                  //
    //******************************************************************************************************************************//
    /**
     *  @brief  Header (Sel: Frame-Sync, Query: Preamble)
     *  @note   only diff between them is addition of TRCal for Preamble
     */
    cmd_dur_cts += NUM_CHIPS_DELIM;                                         /* Delimiter                                            */
    cmd_dur_cts += NUM_CHIPS_DATA0;                                         /* Data-0                                               */
    cmd_dur_cts += NUM_CHIPS_RTCAL;                                         /* RTCal                                                */
    if(type != SELECT) {
        cmd_dur_cts += NUM_CHIPS_TRCAL;                                     /* TRCal                                                */
    }


    //******************************************************************************************************************************//
    //                                                      PACKET                                                                  //
    //******************************************************************************************************************************//
    uint16_t num_bits;
    bool bits[MAX_NUM_BITS];

    i = 0;

    if(type == SELECT) {
        SelectCommand *s = (SelectCommand *) cmd;

        bits[i++] = (s->command & BIT0) > 0;
        bits[i++] = (s->command & BIT1) > 0;
        bits[i++] = (s->command & BIT2) > 0;
        bits[i++] = (s->command & BIT3) > 0;

        bits[i++] = (s->target & BIT0) > 0;
        bits[i++] = (s->target & BIT1) > 0;
        bits[i++] = (s->target & BIT2) > 0;

        bits[i++] = (s->action & BIT0) > 0;
        bits[i++] = (s->action & BIT1) > 0;
        bits[i++] = (s->action & BIT2) > 0;

        bits[i++] = (s->membank & BIT0) > 0;
        bits[i++] = (s->membank & BIT1) > 0;

        for(j=0; j<8; j++) {
            uint8_t mask = (1 << j);
            bits[i++] = (s->pointer & mask) > 0;
        }

        for(j=0; j<8; j++) {
            uint8_t mask = (1 << j);
            bits[i++] = (s->length & mask) > 0;
        }

        for(j=0; j<16; j++) {
            uint8_t mask = (1 << j);
            bits[i++] = (s->mask & mask) > 0;
        }

        bits[i++] = (s->truncate & BIT0) > 0;

        for(j=0; j<16; j++) {
            uint8_t mask = (1 << j);
            bits[i++] = (s->crc16 & mask) > 0;
        }
    } else {
        QueryCommand *q = (QueryCommand *) cmd;

        bits[i++] = (q->command & BIT0) > 0;
        bits[i++] = (q->command & BIT1) > 0;
        bits[i++] = (q->command & BIT2) > 0;
        bits[i++] = (q->command & BIT3) > 0;

        bits[i++] = (q->dr & BIT0) > 0;

        bits[i++] = (q->m & BIT0) > 0;
        bits[i++] = (q->m & BIT1) > 0;

        bits[i++] = (q->trext & BIT0) > 0;

        bits[i++] = (q->sel & BIT0) > 0;
        bits[i++] = (q->sel & BIT1) > 0;

        bits[i++] = (q->session & BIT0) > 0;
        bits[i++] = (q->session & BIT1) > 0;

        bits[i++] = (q->target & BIT0) > 0;

        bits[i++] = (q->q & BIT0) > 0;
        bits[i++] = (q->q & BIT1) > 0;
        bits[i++] = (q->q & BIT2) > 0;
        bits[i++] = (q->q & BIT3) > 0;

        bits[i++] = (q->crc5 & BIT0) > 0;
        bits[i++] = (q->crc5 & BIT1) > 0;
        bits[i++] = (q->crc5 & BIT2) > 0;
        bits[i++] = (q->crc5 & BIT3) > 0;
        bits[i++] = (q->crc5 & BIT4) > 0;
    }

    num_bits = i;


    //Calc Bit Counts
    for(i = 0; i<num_bits; i++) {                                           /* for each bit...                                      */

       //grab the bit
        bool curr_bit = bits[i];

        //update the count
        if(curr_bit) {
            d1_ct++;
        } else {
            d0_ct++;
        }
    }

    //Calc Duration
    cmd_dur_cts += (d0_ct * NUM_CHIPS_DATA0);
    cmd_dur_cts += (d1_ct * NUM_CHIPS_DATA1);


    return cmd_dur_cts;
}

