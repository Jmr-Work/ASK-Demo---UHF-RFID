#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_


//Radio Selection
#define RADIO_SEL_CC1175                                                  /* Uhf-Id's target radio                                */
//#define RADIO_SEL_CC1200                                                    /* Entry-level radio with similar features              */


//Radios
#include "radios/cc1175.h"
#include "radios/cc1200.h"


//Project
#include "mcu.h"
#include "radios/cc1200_reg_config.h"


//Chip Selection
#ifdef RADIO_SEL_CC1200
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1200
    #define preferredSettings           preferredSettings_cc1200
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1200
#endif
#ifdef RADIO_SEL_CC1175
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1175
    #define preferredSettings           preferredSettings_cc1175
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1175
#endif


//Globals
extern void radio_gpio_init(void);
extern void radio_spi_init(void);
extern void radio_init(void);

extern void radio_run_init(void);
extern void radio_run_loop(void);
extern void radio_run_waitForRoom(void);
extern void radio_run_prepForNext(void);

#endif /* BSP_RADIO_H_ */

