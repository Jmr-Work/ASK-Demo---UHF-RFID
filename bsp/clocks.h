#ifndef BSP_CLOCKS_H_
#define BSP_CLOCKS_H_


//Libraries
#include <stdint.h>


//Processor
#include <msp430.h>


//Project
#include "mcu.h"


//Globals
extern void clocks_init(void);

//Defines
#define DCO_MULT_16MHZ          488
#define DCORSEL_16MHZ           DCORSEL_5
#define VCORE_16MHZ             PMMCOREV_1

#define BSP_SYS_CLK_16MHZ       16000000UL

//Globals
extern void clocks_init(void);


//Locals
void jmr_bspMcuSetVCore(uint8_t ui8Level);
void jmr_bspMcuSetVCoreUp(uint8_t ui8Level);
void jmr_bspMcuSetVCoreDown(uint8_t ui8Level);


#endif /* BSP_CLOCKS_H_ */

