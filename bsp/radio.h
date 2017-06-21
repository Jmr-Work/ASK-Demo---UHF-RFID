#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_

//Radios
#include "radios/cc1200.h"


//Project
#include "mcu.h"
#include "radios/cc1200_reg_config.h"


//Radio Selection
//#define RADIO_SEL_CC1175                                                  /* Uhf-Id's target radio                                */
#define RADIO_SEL_CC1200                                                    /* Entry-level radio with similar features              */


//Globals
extern void radio_spi_init(void);
extern void radio_init(void);

extern void radio_run_init(void);
extern void radio_run_loop(void);
extern void radio_run_waitForRoom(void);
extern void radio_run_prepForNext(void);

#endif /* BSP_RADIO_H_ */

