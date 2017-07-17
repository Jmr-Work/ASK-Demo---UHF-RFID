#include "radio_test.h"


//Test Vars
cc12xx_partInfo            info;
cc12xx_marcInfo            marc;
cc12xx_txFifoInfo          fifo;
cc12xx_fifoCfgInfo         cfg;
cc12xx_freqCfgInfo         freq;
cc12xx_freqSynthInfo       synth;
cc12xx_paCfgInfo           paCfg;
cc12xx_extCtrlInfo         extCtrl;
cc12xx_extClockInfo        extClk;
cc12xx_rfEndInfo           rfend;
cc12xx_modemStatusInfo     modem;
cc12xx_rngValInfo          rng[3];
cc12xx_modCfgInfo          mod;
cc12xx_symbolInfo          sym;
cc12xx_pktCfgInfo          pkt;
cc12xx_gpioCfgInfo         gpio;
cc12xx_xoscCfgInfo         xosc;
rfStatus_fields            report;


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

    report = cc12xx_getRFStatusFields(0x80);
    report = cc12xx_getRFStatusFields(0xF0);
    report = cc12xx_getRFStatusFields(0x00);
    report = cc12xx_getRFStatusFields(0x30);

    return;
}

