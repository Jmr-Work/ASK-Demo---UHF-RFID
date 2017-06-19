#include "mcu.h"


/************************************************************************************************************************************/
/** @fcn        void mcu_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void mcu_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    msp430f5438a_init();
#endif

    return;
}



/************************************************************************************************************************************/
/** @fcn        void mcu_enable_interrupts(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void mcu_enable_interrupts(void) {

#ifdef TARGET_IS_MSP430F5438A
    msp430f5438a_enable_interrupts();
#endif


    return;
}


/************************************************************************************************************************************/
/** @fcn        void mcu_demo(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Purpose
 *      x
 *
 *  @param      [in]    name    descrip
 *
 *  @param      [out]   name    descrip
 *
 *  @return     (type) descrip
 *
 *  @pre        x
 *
 *  @post       x
 *
 *  @section    Operation
 *      x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Hazards & Risks
 *      x
 *
 *  @section    Todo
 *      x
 *
 *  @section    Timing
 *      x
 *
 *  @note       x
 */
/************************************************************************************************************************************/
void mcu_demo(void) {

#ifdef TARGETS_MSP430F5438A_H_
    msp430f5438a_demo();
#endif

    return;
}

