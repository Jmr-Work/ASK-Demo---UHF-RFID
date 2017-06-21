#ifndef EMK_RADIO_CONFIGURE_H_
#define EMK_RADIO_CONFIGURE_H_

//Libraries
#include <stdint.h>

//Processor
#include <msp430.h>

//Project
#include "cc1200.h"
#include "cc1200_reg_config.h"


//Globals
extern void radio_configure(void);
extern void radio_reg_read(uint16_t addr, uint8_t *dataPtr);
extern void radio_reg_write(uint16_t addr, uint8_t data);


#endif /* EMK_RADIO_CONFIGURE_H_ */
