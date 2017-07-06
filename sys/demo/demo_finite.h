/**
 *  @file       demo_finite.h
 *  @brief      give a demo of using finite packet mode configuration
 *  @details    this mode is useful often for debug & dev, leaving nearby & functional if needed
 */
#ifndef SYS_DEMO_DEMO_FINITE_H_
#define SYS_DEMO_DEMO_FINITE_H_


//Libraries
#include <stdint.h>


//Processor
#include "../../bsp/mcu.h"


//Project
#include "../../globals.h"


//Radio
#include "../../bsp/radio.h"


//Globals
extern void demo_finite(void);


#endif /* SYS_DEMO_DEMO_FINITE_H_ */
