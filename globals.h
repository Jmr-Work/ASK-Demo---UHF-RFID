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

////Comm Libs
//#include "lib/rfid.h"
//
//
////Defs
//#define TX_BUFF_SIZE        (127)                                          /* continuous tx observed from 2 to 127 (max)            */
//
////Globals
//extern uint8_t tx_buff[TX_BUFF_SIZE];

//Locals
void sys_init(void);


#endif /* GLOBALS_H_ */

