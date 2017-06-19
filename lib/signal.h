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


//Globals
extern void signal_generate(void);
extern void signal_grab_next(void);


#endif /* LIB_SIGNAL_H_ */

