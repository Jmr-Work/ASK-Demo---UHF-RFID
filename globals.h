#ifndef GLOBALS_H_
#define GLOBALS_H_


//Libraries
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


//Processor
#include "bsp/mcu.h"


//Project
#include "bsp/clocks.h"
#include "bsp/timers.h"
#include "bsp/gpio.h"
#include "bsp/radio.h"

//Libs
#include "lib/signal.h"
#include "lib/rfid.h"

//Test & Dev
#include "sys/test/rfid_test.h"


//Defs
#define TX_BUFF_SIZE        (100)                                          /* continuous tx observed from 2 to 127 (max)            */
#define SRC_BUFF_SIZE       (2400)

#define NUM_BITS_IN_BYTE    (8)


//TI CC-Series PARTNUMBER Register Values
#define CHIP_PARTNUMBER_CC1175 (0x5A)                                       /* see [4]  p.105 PARTNUMBER                            */
#define CHIP_PARTNUMBER_CC1120 (0x48)
#define CHIP_PARTNUMBER_CC1121 (0x40)
#define CHIP_PARTNUMBER_CC1125 (0x58)
#define CHIP_PARTNUMBER_CC1200 (0x20)                                       /* see [6]  p.109 PARTNUMBER                            */
#define CHIP_PARTNUMBER_CC1201 (0x21)


//Globals
extern uint8_t tx_buff[TX_BUFF_SIZE];
extern uint8_t data_arr[SRC_BUFF_SIZE];


//Locals
void sys_init(void);


#endif /* GLOBALS_H_ */

