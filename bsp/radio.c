/************************************************************************************************************************************/
/** @file       radio.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/19/17
 *  @last rev   6/19/17
 *
 *
 *  @notes      x
 *
 *  @section    Opens
 *          none current
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "radio.h"


/************************************************************************************************************************************/
/** @fcn        void radio_gpio_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void radio_gpio_init(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_gpio_init();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_gpio_init();
#endif

    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_spi_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void radio_spi_init(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_spi_init();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_spi_init();
#endif
    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void radio_init(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_init();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_init();
#endif
    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void radio_run_init(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_run_init();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_run_init();
#endif
    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void radio_run_loop(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_run_loop();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_run_loop();
#endif
    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void radio_run_waitForRoom(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_run_waitForRoom();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_run_waitForRoom();
#endif
    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void radio_run_prepForNext(void) {

#ifdef RADIO_SEL_CC1200
    cc1200_run_prepForNext();
#endif
#ifdef RADIO_SEL_CC1175
    cc1175_run_prepForNext();
#endif
    return;
}

