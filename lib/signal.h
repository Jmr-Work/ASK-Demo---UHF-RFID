#ifndef LIB_SIGNAL_H_
#define LIB_SIGNAL_H_


//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


//Project
#include "../globals.h"
#include "rfid.h"


//Project
#include "../globals.h"
#include "rfid.h"
#include "commands.h"
#include "utils.h"


//Definitions
#define RFID_CMD_SIZE_MAX       (11)                                        /* size in bytes of largest RFID command                */
#define MSG_COUNT_MAX           (6)                                         /* max number of messages stored for delivery           */

#define NUM_CHIPS_IN_725_US     (725 / 12.5)
#define NUM_CHIPS_IN_1_MS       (1000 / 12.5)
#define NUM_CHIPS_IN_3_MS       (3000 / 12.5)
#define NUM_CHIPS_DELIM         (1)
#define NUM_CHIPS_DATA0         (2)
#define NUM_CHIPS_DATA1         (4)
#define NUM_CHIPS_RTCAL         (6)
#define NUM_CHIPS_TRCAL         (17)

#define NUM_CHIPS_SLICE         (TX_BUFF_SIZE)                              /* for now, simplest answer                             */

/**
 *  @title  RFID command for waveform insertion & transmit
 *  @note   leave idle_ct value as '0' to skip
 */
typedef struct message_t {
    uint8_t type;                                                           /* stored as command_t, left as u8 to force size        */

    uint32_t pre_idle_high_ct;                                              /* (H) hold-off counts from last message before start   */
    uint32_t post_idle_high_ct;                                             /* (H) idle counts after message complete               */
    uint32_t exit_idle_low_ct;                                              /* (L) idle counts after post_idle_high duration        */

    uint8_t data[RFID_CMD_SIZE_MAX];                                        /* message contents (array placeholder)                 */

    //Calculated Vars
    uint32_t t_start;
    uint32_t t_end;
    uint32_t t_dur;
} Message;


//Transmit Waveform
typedef struct waveform_t {
    Message  msgs[MSG_COUNT_MAX];                                            /* RFID messages to Tx!                                 */
    uint16_t msg_count;                                                      /* number of messages loaded in msgs                    */
    bool     mode;
} Waveform;


//Globals
extern void signal_generate(void);
extern void signal_grab_next(void);


//Locals
static void load_command(Command type, uint8_t *cmd, uint32_t *idle_cts);
Message *get_current_msg(Waveform wvfm, uint32_t t_curr);
uint32_t calc_wvfm_duration(Waveform wvfm);
uint32_t calc_msg_duration(Command type, uint8_t *cmd);

extern /*static*/ void signal_grab_next_rxt1(void);


#endif /* LIB_SIGNAL_H_ */

