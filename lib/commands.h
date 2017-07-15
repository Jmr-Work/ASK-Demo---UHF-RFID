#ifndef LIB_COMMANDS_H_
#define LIB_COMMANDS_H_


//Definitions
#define NUM_QUERY_BITS      (22)
#define NUM_SELECT_BITS     (61)
#define MAX_NUM_BITS        (NUM_SELECT_BITS)


//RFID Command Types
typedef enum command_t {
    SELECT    = 0x00,
    QUERY     = 0x01,
    QUERY_REP = 0x02,
    QUERY_ACK = 0x03,
    REQ_RN    = 0x04,
    ACCESS    = 0x05,
    LOCK      = 0x06,
    READ      = 0x07,
    WRITE     = 0x08,
    BLWRITE   = 0x09,
    BLERASE   = 0x0A,
    BLPERM    = 0x0B,
    IDLE_H    = 0x0C,
    IDLE_L    = 0x0D
} Command;


//Query - [1] Sec 9.3.2.11.2.1 - p.179 (PDF p.201)
typedef struct query_command_t {
    uint8_t command;                                                        /* (4b)                                                 */
    uint8_t dr;                                                             /* (1b)                                                 */
    uint8_t m;                                                              /* (2b)                                                 */
    uint8_t trext;                                                          /* (1b)                                                 */
    uint8_t sel;                                                            /* (2b)                                                 */
    uint8_t session;                                                        /* (2b)                                                 */
    uint8_t target;                                                         /* (1b)                                                 */
    uint8_t q;                                                              /* (4b)                                                 */
    uint8_t crc5;                                                           /* (5b)                                                 */
} QueryCommand;


//Select - [1] Sec 9.3.2.11.1.1 - p.177 (PDF p.199)
//@note     we use fixed 16-bit masks
typedef struct select_command_t {
    uint8_t  command;                                                       /* (4b)                                                 */
    uint8_t  target;                                                        /* (3b)                                                 */
    uint8_t  action;                                                        /* (3b)                                                 */
    uint8_t  membank;                                                       /* (2b)                                                 */
    uint8_t  pointer;                                                       /* (8b)                                                 */
    uint8_t  length;                                                        /* (8b)                                                 */
    uint16_t mask;                                                          /* (16b)                                                */
    uint8_t  truncate;                                                      /* (1b)                                                 */
    uint16_t crc16;                                                         /* (16b)                                                */
} SelectCommand;


#endif /* LIB_COMMANDS_H_ */

