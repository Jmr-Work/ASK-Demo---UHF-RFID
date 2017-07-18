#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_


//Radio Selection
#define RADIO_SEL_CC1175                                                  /* Uhf-Id's target radio                                */
//#define RADIO_SEL_CC1200                                                    /* Entry-level radio with similar features              */


//Project
#include "mcu.h"


//Radios
#include "radios/cc12xx_reg_config_names.h"


//Radio Selection
#ifdef RADIO_SEL_CC1200
    #include "radios/cc1200.h"
    #include "radios/cc1200_reg_config.h"
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1200
    #define preferredSettings           preferredSettings_cc1200
    #define radio_reg_names             cc1200_names
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1200

    #define radio_init                  cc1200_init
    #define radio_run_init              cc1200_run_init
    #define radio_run_loop              cc1200_run_loop
    #define radio_run_waitForRoom       cc1200_run_waitForRoom
    #define radio_run_prepForNext       cc1200_run_prepForNext
#endif
#ifdef RADIO_SEL_CC1175
    #include "radios/cc1175.h"
    #include "radios/cc1175_reg_config.h"
    #define CHIP_PARTNUMBER_UHF_ID      CHIP_PARTNUMBER_CC1175
    #define preferredSettings           preferredSettings_cc1175
    #define radio_reg_names             cc1175_names
    #define NUM_PREFERRED_SETTINGS      NUM_PREFERRED_SETTINGS_CC1175

    #define radio_init                  cc1175_init
    #define radio_run_init              cc1175_run_init
    #define radio_run_loop              cc1175_run_loop
    #define radio_run_waitForRoom       cc1175_run_waitForRoom
    #define radio_run_prepForNext       cc1175_run_prepForNext
#endif


//Radio Defs (clean code)
#ifdef RADIO_SEL_CC1200
    #define CC12XX_PKT_CFG0     CC120X_PKT_CFG0
    #define CC12XX_PKT_LEN      CC120X_PKT_LEN
    #define CC12XX_NUM_TXBYTES  CC120X_NUM_TXBYTES
    #define CC12XX_SFTX         CC120X_SFTX
    #define CC12XX_STX          CC120X_STX
#endif
#ifdef RADIO_SEL_CC1175
    #define CC12XX_PKT_CFG0     CC112X_PKT_CFG0
    #define CC12XX_PKT_LEN      CC112X_PKT_LEN
    #define CC12XX_NUM_TXBYTES  CC112X_NUM_TXBYTES
    #define CC12XX_SFTX         CC112X_SFTX
    #define CC12XX_STX          CC112X_STX
#endif


//Globals
extern void radio_init(void);
extern void radio_run_init(void);
extern void radio_run_loop(void);
extern void radio_run_waitForRoom(void);
extern void radio_run_prepForNext(void);

#define radio_spi_init  mcu_radio_spi_init                                  /* for cleanliness of presentation in main.c            */


//Global Vars
#define NUM_PREFERRED_SETTINGS_CC1175   (51)                                /* @open    IAR bug, compilation fails with IAR w/o     */
extern const char radio_reg_names[NUM_PREFERRED_SETTINGS][20];

#endif /* BSP_RADIO_H_ */

