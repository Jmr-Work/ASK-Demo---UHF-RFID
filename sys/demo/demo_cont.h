/**
 *  @file       demo_cont.h
 *  @brief      give a demo of using finite packet mode configuration
 *  @details    this mode is useful often for debug & dev, leaving nearby & functional if needed
 */
#ifndef SYS_DEMO_CONT_H_
#define SYS_DEMO_CONT_H_


//Libraries
#include <stdint.h>


//Processor
#include "../../bsp/mcu.h"


//Project
#include "../../globals.h"


//Radio
#include "../../bsp/radio.h"


//Globals
extern void demo_cont(void);


#endif /* SYS_DEMO_CONT_H_ */
