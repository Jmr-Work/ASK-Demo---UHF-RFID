/************************************************************************************************************************************/
/** @file       x
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
#include "demo_slice.h"



volatile     uint16_t loop_ct = 0;


/************************************************************************************************************************************/
/** @fcn        void demo_slice(void)
 *  @brief      load a waveform by slice
 *  @details    x
 *
 *  @section    Waveform
 *      see load_next_slice() hdr
 */
/************************************************************************************************************************************/
void demo_slice(void) {

    load_next_slice();

    radio_run_init();

    for(;;) {
        radio_run_loop();

        load_next_slice();

        radio_run_waitForRoom();

        radio_run_prepForNext();

        loop_ct++;
    } /* end for(;;)            */
}


//Temp Dev Vars
#define WAVEFORM_SIZE           (1000)
#define SLICE_SIZE              (100)

#define N_SLICE1                ((40000/12.5))                                /* time value in radio ticks                            */
#define N_SLICE2                ((50000/12.5) + N_SLICE1)
#define N_SLICE3                ((10000/12.5)  + N_SLICE2)
#define N_SLICE4                ((100000/12.5) + N_SLICE3)


static int32_t t_slice = -SLICE_SIZE;                                       /* start index of last slice in the waveform            */


/************************************************************************************************************************************/
/** @fcn        static void load_next_slice(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Theory
 *      For Slice Mode, there is a waveform description loaded into the global (Waveform) wvfm. On each call to load_slice() you grab
 *      the contents of the next slice from the waveform, toss into the TX FIFO and return in the same format as Continuous Mode
 *
 *  @section    Waveform [... 400 ... 725 ... 50 ... 125 ...]
 *      t_on  = 40ms
 *      t_off = 50ms
 *      t_on  = 10ms
 *      t_off = 100ms
 *
 *  @assum      loading on even num of bits in byte, loading complete bytes
 *
 *  @note       units of 't' here are chips (12.5us)
 *
 *  @section    Opens
 *      delineate & separate byte_index & bit_index, and be careful of ref (bytewise or wvfm-wise!)
 *      t - byte index within the wvfm
 *      b - bit index within the wvfm
 *      tb - bit index within the current byte
 */
/************************************************************************************************************************************/
static void load_next_slice(void) {

    volatile uint32_t test[] = {N_SLICE1, N_SLICE2, N_SLICE3, N_SLICE4};

    //find next slice location
    uint32_t t_slice_next = (t_slice + SLICE_SIZE) % WAVEFORM_SIZE;

    uint32_t b_curr_bit = (t_slice_next*NUM_BITS_IN_BYTE);                  /* start grabbing at front of t_slice_next              */

    uint8_t curr_byte = 0;
    uint8_t curr_bit  = BIT0;

    //Load the contents of this slice, bitwise into tx_buff
    while(curr_byte < TX_BUFF_SIZE) {

        bool bit;

        //Find Segment you are in, snatch bit
        if(b_curr_bit < N_SLICE1) {                                         /* b_curr_bit is the equiv of curr timestamp            */
            bit = true;
        } else if(b_curr_bit < N_SLICE2) {
            bit = false;
        } else if(b_curr_bit < N_SLICE3) {
            bit = true;
        } else {
            bit = false;
        }

        //Load Bit
        if(bit) {
            tx_buff[curr_byte] |= (1 << (curr_bit-1));
        } else {
            tx_buff[curr_byte] &= ~(1 << (curr_bit-1));
        }

        //Update Loc
        if(++curr_bit > NUM_BITS_IN_BYTE) {
            curr_byte++;
            curr_bit = 0;
        }

        b_curr_bit = (b_curr_bit + 1) % (WAVEFORM_SIZE*BITS_IN_BYTE);       /* Next bit                                             */
    }

    //Send Tx Buff
    //@todo!

    //Update t_slice for new slice loaded
    t_slice = t_slice_next;
}
