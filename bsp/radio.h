#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_


//Radio Selection
#define RADIO_SEL_CC1175                                                  /* Uhf-Id's target radio                                */
//#define RADIO_SEL_CC1200                                                    /* Entry-level radio with similar features              */


//Project
#include "mcu.h"


//Radio Selection
#ifdef RADIO_SEL_CC1200
    #include "radios/cc1200.h"
    #include "radios/cc1200_reg_config.h"
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1200
    #define preferredSettings           preferredSettings_cc1200
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1200
#endif
#ifdef RADIO_SEL_CC1175
    #include "radios/cc1175.h"
    #include "radios/cc1175_reg_config.h"
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1175
    #define preferredSettings           preferredSettings_cc1175
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1175
#endif


//Globals
extern void radio_init(void);
extern void radio_run_init(void);
extern void radio_run_loop(void);
extern void radio_run_waitForRoom(void);
extern void radio_run_prepForNext(void);

#define radio_gpio_init     mcu_radio_gpio_init                             /* for cleanliness of presentation in main.c            */
#define radio_spi_init      mcu_radio_spi_init
#define radio_spi_tx        mcu_radio_spi_tx

#endif /* BSP_RADIO_H_ */

