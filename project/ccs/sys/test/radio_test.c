#include "radio_test.h"

//Test Vars (volatile to avoid silly debug inspect...)
volatile cc12xx_partInfo            info;
volatile cc12xx_marcInfo            marc;
volatile cc12xx_txFifoInfo          fifo;
volatile cc12xx_fifoCfgInfo         cfg;
volatile cc12xx_freqCfgInfo         freq;
volatile cc12xx_freqSynthInfo       synth;
volatile cc12xx_paCfgInfo           paCfg;
volatile cc12xx_extCtrlInfo         extCtrl;
volatile cc12xx_extClockInfo        extClk;
volatile cc12xx_rfEndInfo           rfend;
volatile cc12xx_modemStatusInfo     modem;
volatile cc12xx_rngValInfo          rng[3];
volatile cc12xx_modCfgInfo          mod;
volatile cc12xx_symbolInfo          sym;
volatile cc12xx_pktCfgInfo          pkt;
volatile cc12xx_gpioCfgInfo         gpio;
volatile cc12xx_xoscCfgInfo         xosc;


/************************************************************************************************************************************/
/** @fcn        void radio_reg_lib_test(void)
 *  @brief      read each of the reg groups in library
 *  @details    y
 */
/************************************************************************************************************************************/
void radio_reg_lib_test(void) {

    info = cc12xx_get_partInfo();

    marc = cc12xx_get_marcInfo();

    fifo = cc12xx_get_txFifoInfo();

    cfg  = cc12xx_get_fifoCfgInfo();

    freq = cc12xx_get_freqInfo();

    synth = cc12xx_get_freqSynthInfo();

    paCfg = cc12xx_get_paCfgInfo();

    extCtrl = cc12xx_get_extCtrlInfo();

    extClk = cc12xx_get_extClockInfo();

    rfend = cc12xx_get_rfEndInfo();

    modem = cc12xx_get_ModemInfo();

    rng[0] = cc12xx_get_rngValInfo();                                       /* multiple reads to verify RNG                         */
    rng[1] = cc12xx_get_rngValInfo();
    rng[2] = cc12xx_get_rngValInfo();

    mod =  cc12xx_get_modCfgInfo();

    sym =  cc12xx_get_symbolInfo();

    pkt =  cc12xx_get_pktCfgInfo();

    gpio = cc12xx_get_gpioCfgInfo();

    xosc = cc12xx_get_xoscCfgInfo();

    return;
}

