#ifndef BSP_RADIOS_CC1175_H_
#define BSP_RADIOS_CC1175_H_

//Radio
#include "cc12xx.h"


//Globals
extern void cc1175_init(void);
extern void cc1175_run_init(void);
extern void cc1175_run_loop(void);
extern void cc1175_run_waitForRoom(void);
extern void cc1175_run_prepForNext(void);


#endif /* BSP_RADIOS_CC1175_H_ */

