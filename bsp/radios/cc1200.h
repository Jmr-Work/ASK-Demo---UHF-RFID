#ifndef EMK_CC1200_H_
#define EMK_CC1200_H_


//Libraries
#include <stdint.h>

//Processor
#include "../mcu.h"


//Radio
#include "cc12xx.h"
#include "cc1200_reg_config.h"


//Globals
extern void cc1200_init(void);
extern void cc1200_run_init(void);
extern void cc1200_run_loop(void);
extern void cc1200_run_waitForRoom(void);
extern void cc1200_run_prepForNext(void);


#endif /* EMK_CC1200_H_ */

