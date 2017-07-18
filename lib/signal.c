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
 *      Bit		 - RFID Data-bit (e.g. Data-0 or Data-1)
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


//Signal Generation
uint32_t t_curr;                                                            /* current timestamp in slice acquisition               */
uint32_t t_curr_stamp;                                                      /* entry timestamp to current slice                     */


/************************************************************************************************************************************/
/** @fcn        void signal_generate(void)
 *  @brief      generate the RFID signal for use in the project
 *  @details    x
 *
 *  @post       waveform is ready for use by transmit library
 *
 *  @section   Message Contents
 *      Idle-High   150 us
 *      Select
 *      Idle-High   725 us
 *      Query
 *      Idle-High   150 us
 *      Idle-Low    2.0 ms
 *
 *  @post   wvfm initialized
 *          tx_buff = {0}
 *
 *  @section   Opens
 *      Generate contents of q & s
 *      specify correct timing values
 *      generate routines to calculate CRC5 & CRC16
 */
/************************************************************************************************************************************/
void signal_generate(void) {

    uint8_t i;

    //Pre (tx_buff set to 0)
    for(i=0; i<TX_BUFF_SIZE; i++) {
        tx_buff[i] = 0x00;
    }

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

    //Init timestamp
    t_curr = 0;                                                             /* start slice generation at the beginning              */

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
 *      Finite Demo
 *      Continuous Demo
 *      RFID Demo
 *
 *      Validate all indexing math here in RFID demo section
 *
 *  @section    RFID Waveform Operation
 *      The signal is held within Waveform and is a series of messages, each with data contents & specified timing vals (pre/post)
 *
 *      Waveform
 *          msg[] <- cast to specified message (Select, Query, etc.)
 *
 *  @pre    t_curr is loaded with active time to begin generation from (e.g. t_curr=0 right at the start)
 *  @post   new slice is loaded to the Tx Buffer (tx_buff)
 *
 *  @note   units of time 't' here are chips of Radio-Tx (e.g. 12.5us per chip)
 */
/************************************************************************************************************************************/
void signal_grab_next(void) {

    uint32_t t_wvfm = calc_wvfm_duration(wvfm);

#ifdef DEMO_SEL_RFID

    //1. Identify location within the waveform
    //(already loaded)

    //2. Identify Message & location within the message
    //walk down the message
//??    Message curr_msg = get_current_msg(wvfm, t_curr);



    //...
    //Grab the current message
    //...



    //N. Update location
    t_curr = (t_curr+NUM_CHIPS_SLICE) % t_curr_stamp;

#else
    for(;;);                                                                /* @open                                                */
#endif




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
/** @fcn        Message *get_current_msg(Waveform wvfm, uint32_t t_curr)
 *  @brief      get the current message
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in] (Message) wvfm - Waveform
 *  @param      [in] (uint32_t) t_curr - current timestamp into the waveform
 *
 *  @return     (Message *) current message pointer into the waveform
 */
/************************************************************************************************************************************/
Message *get_current_msg(Waveform wvfm, uint32_t t_curr) {

    Message *msg;
    bool found = false;
    uint8_t msg_ind;
    //uint32_t t;

    //Setup
    //t = 0;
    msg_ind = 0;


    while(!found) {

        //Grab Next Message
        msg = &wvfm.msgs[msg_ind];
    }


    return msg;
}


/************************************************************************************************************************************/
/** @fcn        uint32_t calc_wvfm_duration(Waveform wvfm)
 *  @brief      calculate the duration of a waveform
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in] (Waveform) wvfm - waveform to perform calculation on
 *
 *  @return (uint32_t) time of waveform [chips]
 *
 *  @assum  all loaded messages have set & valid time values
 *
 *  @section    Opens
 *      test & validate
 */
/************************************************************************************************************************************/
uint32_t calc_wvfm_duration(Waveform wvfm) {

    uint32_t t_total = 0;

    uint32_t i;

    for(i=0; i<wvfm.msg_count; i++) {

        //Grab Current Message
        Message msg = wvfm.msgs[i];

        //Append Timing Values
        t_total += msg.pre_idle_high_ct;
        t_total += msg.post_idle_high_ct;
        t_total += msg.exit_idle_low_ct;

        //Append Signal
        t_total += calc_msg_duration((Command) msg.type, msg.data);
    }

    return t_total;
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


/************************************************************************************************************************************/
/** @fcn        static void signal_grab_next_rxt1(void)
 *  @brief      Generate the static waveform for Rx-Testing #1 ('rxt1')
 *  @details    x
 *
 *  @section    Source
 *      Static RFID Wvfms#cc80 ('rxt1')
 *      /Query/Reader Result/Reader Results.xlsx:3a
 *
 *  @dest       tx_buff directly
 *
 *  @section    3a Contents (1000100100000000001011)
 *          Cmd     0b1000
 *          DR      0b1 (DR=64/3)
 *          M       0b00
 *          Trext   0b1
 *          Sel     0b00
 *          Sess    0b00
 *          Tgt     0b0
 *          Q       0b0000
 *          CRC-5   0b01011
 *
 *  @section    3a Timing
 *      Scope Measure: 920us
 *          D0:    2 Chips
 *          D1:    3 Chips
 *          RTCal: 63 us
 *          TRCal: 85 us
 *          Msg:   628us
 *      Calc:
 *          Total: 885us
 *          Delim: 12.5us
 *          D0:    25 us
 *          D1:    37.5 us
 *          RTCal: 62.5 us (D0+D1 - 62.5 us)
 *          TRCal: 85.33 us (DR/BLF -> (64/3)/250k -> 85.33 us)
 *          Msg: (6*1, 16*0) -> 625 us
 *
 *  @pre    tx_buff = {0}
 *
 *  @note   see '3a - Query - 1238917910(2).bmp' for illustration
 */
/************************************************************************************************************************************/
/*static*/ void signal_grab_next_rxt1(void) {

    //------------------------------------------Load into buffer--------------------------------------------------------------------//
    dataBitGenLoc loc = {
        .arr_ind = 0,
        .byte_ind = 0
    };

    //Preamble
    loc = rfid_sig_idleRF(tx_buff, loc, NUM_CHIPS_IN_1_MS, true);           /* Idle-High (1ms)                                      */
    loc = rfid_sig_delim(tx_buff, loc);                                     /* Delim                                                */
    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* Data-0                                               */
    loc = rfid_sig_RTCal(tx_buff, loc);                                     /* RTCal                                                */
    loc = rfid_sig_RTCal(tx_buff, loc);                                     /* TRCal                                                */

    //------------------------------------------------------Message-----------------------------------------------------------------//
    loc = rfid_sig_dataBit(tx_buff, loc, true);                             /* Command - 0b1000                                           */
    loc = rfid_sig_dataBit(tx_buff, loc, false);
    loc = rfid_sig_dataBit(tx_buff, loc, false);
    loc = rfid_sig_dataBit(tx_buff, loc, false);

    loc = rfid_sig_dataBit(tx_buff, loc, true);                             /* DR - 0b1                                             */

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* M - 0b00                                             */
    loc = rfid_sig_dataBit(tx_buff, loc, false);

    loc = rfid_sig_dataBit(tx_buff, loc, true);                             /* TRext - 0b1                                          */

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* Sel - 0b00                                           */
    loc = rfid_sig_dataBit(tx_buff, loc, false);

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* Sess - 0b00                                          */
    loc = rfid_sig_dataBit(tx_buff, loc, false);

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* Tgt - 0b0                                            */

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* Q - 0b0000                                           */
    loc = rfid_sig_dataBit(tx_buff, loc, false);
    loc = rfid_sig_dataBit(tx_buff, loc, false);
    loc = rfid_sig_dataBit(tx_buff, loc, false);

    loc = rfid_sig_dataBit(tx_buff, loc, false);                            /* CRC5 - 0b01011                                       */
    loc = rfid_sig_dataBit(tx_buff, loc, true);
    loc = rfid_sig_dataBit(tx_buff, loc, false);
    loc = rfid_sig_dataBit(tx_buff, loc, true);
    loc = rfid_sig_dataBit(tx_buff, loc, true);

    //Exit Values
    loc = rfid_sig_idleRF(tx_buff, loc, NUM_CHIPS_IN_3_MS, true);           /* Idle-High (3ms)                                      */

    //Idle-Low (Remainder, all 0's already on init config)

    //<TEMP>
//    tx_buff[60] = 0xFF;
//    tx_buff[80] = 0x80;
    //</TEMP>


    return;
}

