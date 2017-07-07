/************************************************************************************************************************************/
/** @file       demo_cont.c
 *  @brief      x
 *  @details    x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    7/5/17
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
#include "demo_cont.h"


/************************************************************************************************************************************/
/** @fcn        void demo_cont(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Opens
 *      x
 *
 *  @section    Waveform (see signal.c:signal_generate()
 *      Pre: .        Idle-Off    []
 *      [0]: (200 us) Idle-CW     [200us]
 *      [1]: .        Select      [3162.5us]
 *      [2]: (200 us) Idle-CW     [200us]
 *      [3]: .        Query       [1425us]
 *      [4]: (400 ms) Idle-CW     [400us]
 *      [5]: .        Idle-Off    [1000us]

 *  @note       x
 */
/************************************************************************************************************************************/
void demo_cont(void) {

    uint16_t loop_ct = 0;

    //Generate Waveform
//! signal_generate();
    signal_grab_next();

    radio_run_init();

    for(;;) {
//!     P4OUT |= BIT7;                                                      /* BIT7 pulse: 101ms                                    */

        radio_run_loop();

        signal_grab_next();

        radio_run_waitForRoom();

//!     P4OUT &= ~BIT7;

        radio_run_prepForNext();

        loop_ct++;

//!     P4OUT ^= BIT6;
    } /* end for(;;)            */
}

