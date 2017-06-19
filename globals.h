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
//#include "lib/rfid.h"


//Defs
#define TX_BUFF_SIZE        (100)                                          /* continuous tx observed from 2 to 127 (max)            */
#define SRC_BUFF_SIZE       (2000)

//Globals
extern uint8_t tx_buff[TX_BUFF_SIZE];
extern uint8_t data_arr[SRC_BUFF_SIZE];


//Locals
void sys_init(void);


#endif /* GLOBALS_H_ */

