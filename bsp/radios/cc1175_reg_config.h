#ifndef EMK_CC1175_SIMPLE_LINK_REG_CONFIG_H_
#define EMK_CC1175_SIMPLE_LINK_REG_CONFIG_H_


//Libraries
#include <stdint.h>


//Project
#include "../../globals.h"
#include "temp_radio.h"

//Definitions
#define NUM_PREFERRED_SETTINGS_CC1175    (51)


//Global Vars
extern const registerSetting_t preferredSettings_cc1175[NUM_PREFERRED_SETTINGS_CC1175];


#endif /* EMK_CC1175_SIMPLE_LINK_REG_CONFIG_H_ */

