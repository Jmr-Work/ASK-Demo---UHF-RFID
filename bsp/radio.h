#ifndef BSP_RADIO_H_
#define BSP_RADIO_H_

//Radios
#include "radios/cc1200.h"


//Project
#include "mcu.h"
#include "radios/cc1200_reg_config.h"


//Globals
extern void radio_spi_init(void);
extern void radio_init(void);


#endif /* BSP_RADIO_H_ */

