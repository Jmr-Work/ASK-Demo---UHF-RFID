#include "cc2541_demo.h"



/************************************************************************************************************************************/
/** @fcn        void cc2541_demo(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Waveform (see signal.c:signal_generate()
 *      Pre: .        Idle-Off    []
 *      [0]: (200 us) Idle-CW     [200us]
 *      [1]: .        Select      [3162.5us]
 *      [2]: (200 us) Idle-CW     [200us]
 *      [3]: .        Query       [1425us]
 *      [4]: (400 ms) Idle-CW     [400us]
 *      [5]: .        Idle-Off    [1000us]
 */
/************************************************************************************************************************************/
void cc2541_demo(void) {
  
    uint16_t loop_ct = 0;

    //Generate Waveform
//! signal_generate();
    signal_grab_next();

    radio_run_init();

    for(;;) {

        //DBG-1 HIGH

        radio_run_loop();

        signal_grab_next();

        radio_run_waitForRoom();

        //DBG-1 LOW

        radio_run_prepForNext();

        loop_ct++;

        //DBG-2 TOGGLE

    } /* end for(;;)            */
}

