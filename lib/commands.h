#ifndef LIB_COMMANDS_H_
#define LIB_COMMANDS_H_


//Query - [1] Sec 9.3.2.11.2.1 - p.179 (PDF p.201)
typedef struct queryCommand {
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
typedef struct selectCommand{
    uint8_t  command;                                                       /* (4b)                                                 */
    uint8_t  target;                                                        /* (3b)                                                 */
    uint8_t  action;                                                        /* (3b)                                                 */
    uint8_t  membank;                                                       /* (2b)                                                 */
    uint8_t  pointer;                                                       /* (8b)                                                 */
    uint8_t  length;                                                        /* (8b)                                                 */
    uint16_t mask;                                                          /* (16b)                                                */
    uint8_t  truncate;                                                      /* (1b)                                                 */
    uint8_t  crc16;                                                         /* (16b)                                                */
} SelectCommand;


#endif /* LIB_COMMANDS_H_ */

