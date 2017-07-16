/**
 *  @brief      slice mode is the resource efficient way to perform continuous-tx of RFID waveforms and will be used in the
 *              final deliverable
 */
#ifndef SYS_DEMO_SLICE_H_
#define SYS_DEMO_SLICE_H_


//Libraries
#include <stdint.h>


//Processor
#include "../../bsp/mcu.h"


//Project
#include "../../globals.h"


//Radio
#include "../../bsp/radio.h"


//Globals
extern void demo_slice(void);


//Locals
static void load_next_slice(void);


#endif  /*  SYS_DEMO_SLICE_H_  */

