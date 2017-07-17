#ifndef SYS_DEMO_DEMO_H_
#define SYS_DEMO_DEMO_H_


//Demo Selection
#define DEMO_SEL_FINITE         (0)                                         /* run the finite tx demo                               */
//#define DEMO_SEL_CONT         (1)                                         /* run the continuous tx demo                           */
//#define DEMO_SEL_REG          (2)                                         /* run the register read demo                           */
//#define DEMO_SEL_MAP          (3)                                         /* run the map read & print demo                        */
//#define DEMO_SEL_OTHERS       (123)


//Demo Selection
#ifdef DEMO_SEL_FINITE
    #include "demo_finite.h"
#endif
#ifdef DEMO_SEL_CONT
    #include "demo_cont.h"
#endif
#ifdef DEMO_SEL_REG
    #include "demo_register.h"
#endif
#ifdef DEMO_SEL_MAP
    #include "demo_map.h"
#endif
#ifdef DEMO_SEL_OTHERS
    #include "demo_others.h"
#endif



#endif /* SYS_DEMO_DEMO_H_ */
