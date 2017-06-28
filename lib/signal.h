#ifndef LIB_SIGNAL_H_
#define LIB_SIGNAL_H_


//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


//Project
#include "../globals.h"
#include "rfid.h"


//Defines
#define  b1010		0x0A                                                    /* @brief   temp location here, move to cc2541 header   */
#define  b011		0x03	                                                /* @open    make support TI notation as well            */
#define  b000		0x00
#define  b01		0x01
#define  b00000000	0x00
#define  b00010000	0x10
#define  b0			0x00
#define  b1000		0x08
#define  b0			0x00
#define  b00		0x00
#define  b1			0x01
#define  b00		0x00
#define  b11		0x03
#define  b1			0x01
#define  b0000		0x00
#define  b00000		0x00


//Globals
extern void signal_generate(void);
extern void signal_grab_next(void);

extern uint16_t signal_size;


#endif /* LIB_SIGNAL_H_ */

