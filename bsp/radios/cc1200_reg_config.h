#ifndef EMK_CC1200_SIMPLE_LINK_REG_CONFIG_H_
#define EMK_CC1200_SIMPLE_LINK_REG_CONFIG_H_


//Libraries
#include <stdint.h>


//Typedefs
typedef struct
{
  uint16_t  addr;
  uint8_t   data;
} registerSetting_t;


//Global Vars
extern const registerSetting_t preferredSettings[];


#endif /* EMK_CC1200_SIMPLE_LINK_REG_CONFIG_H_ */

