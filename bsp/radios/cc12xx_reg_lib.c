/************************************************************************************************************************************/
/** @file       cc12xx_reg_lib.c
 *  @brief      register & chip status access for cc12xx family radios
 *  @details    x
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    7/5/17
 *  @last rev   7/5/17
 *
 *
 *  @notes      any registers listed & reported in this file left without descr (e.g. fields) or notes is reported fo
 *
 *  @section    Opens
 *      Verify each routine works, for BOTH radios (dev starts with CC1200!)
 *      List out expected reset vals to find
 *      Have firmware validate reset values on radio before proceeding
 *      Chip Status Byte readout
 *      Write register values
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "cc12xx_reg_lib.h"


/************************************************************************************************************************************/
/** @fcn        cc12xx_partInfo cc12xx_get_partInfo(void)
 *  @brief      get the PARTNUMBER & PARTVERSION
 *
 *  @param      [out]   (cc12xx_partInfo)    part identification info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      PARTNUMBER  - (0x2F8F) Part Number
 *          b7:b0   -   PARTNUM  Chip ID
 *
 *      PARTVERSION - (0x2F90) Part Revision
 *          b7:b0   -   PARTVER  Chip Revision
 *
 *  @section    Chip IDs
 *      0x40 - CC1121
 *      0x48 - CC1120
 *      0x58 - CC1125
 *      0x5A - CC1175
 *
 *  @section    Example
 *      CC1200EM rev1.1.1    - 0x20, 0x11
 *      CC1175DK_EM rev1.1.0 - 0x5A, 0x21
 *
 *  @note       these values reset to 0 and are not immediately ready for reading on boot or reset
 */
/************************************************************************************************************************************/
cc12xx_partInfo cc12xx_get_partInfo(void) {

    cc12xx_partInfo part;

    //Read Registers
    cc12xxSpiReadReg(CC120X_PARTNUMBER,  &part.reg_partnumber,  1);
    cc12xxSpiReadReg(CC120X_PARTVERSION, &part.reg_partversion, 1);

    //Store Values
    part.number  = part.reg_partnumber;
    part.version = part.reg_partversion;

    return part;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_marcInfo cc12xx_get_marcInfo(void)
 *  @brief      get information on MARC status from register map
 *
 *  @param      [out]   (cc12xx_marcInfo)    all MARC content from register map
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      MARC_SPARE    - (0x2F03)  MARC Spare
 *      MARCSTATE     - (0x2F73)  MARC State
 *          b6:b5     -     MARC_2PIN_STATE - MARC2 pin state (TX/RX/IDLE)
 *          b4:b0     -     MARC_STATE      - State of the radio
 *      MARC_STATUS0  - (0x2F95) MARC Status Reg. 0
 *      MARC_STATUS1  - (0x2F94) MARC Status Reg. 1
 *          b7:b0     -     MARC_STATUS_OUT - Source of MCU_WAKEUP assertion
 *
 *  @note       'MARC' denotes "Main Radio Controller", the partner to the onboard 16-bit MCU which runs the cc12xx
 */
/************************************************************************************************************************************/
cc12xx_marcInfo cc12xx_get_marcInfo(void) {

    cc12xx_marcInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_MARC_SPARE,   &info.reg_marcspare,   1);
    cc12xxSpiReadReg(CC120X_MARCSTATE,    &info.reg_marcstate,   1);
    cc12xxSpiReadReg(CC120X_MARC_STATUS0, &info.reg_marcstatus0, 1);
    cc12xxSpiReadReg(CC120X_MARC_STATUS1, &info.reg_marcstatus1, 1);

    //Store Values
    info.pinState   = (info.reg_marcstate && 0x60) >> 5;
    info.marcState  = (marc_state_t) ((info.reg_marcstate && 0x1F) >> 0);   /* @note    typedef for marc_state_t matches bitwise    */
    info.marcStatus = (info.reg_marcstatus1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_txFifoInfo cc12xx_get_txFifoInfo(void)
 *  @brief      get information on TX FIFO status from register map
 *
 *  @param      [out]   (cc12xx_txFifoInfo)    tx fifo information
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      TXFIRST          - (0x2FD3) TX FIFO Pointer First Entry
 *          b7:b0        -      TX_FIRST (e.g. '0x01' for '0x3F01')
 *      TXLAST           - (0x2FD5) TX FIFO Pointer Last Entry
 *          b7:b0        -      TX_LAST (e.g. "")
 *      NUM_TXBYTES      - (0x2FD6) TX FIFO Status
 *          b7:b0        -      TXBYTES - Number of bytes in the TX FIFO
 *      FIFO_NUM_TXBYTES - (0x2FD8) TX FIFO Status
 *          b3:0         -      FIFO_TXBYTES - Number of free entries in the TX FIF0 (15 max reported)
 */
/************************************************************************************************************************************/
cc12xx_txFifoInfo cc12xx_get_txFifoInfo(void) {

    cc12xx_txFifoInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_TXFIRST,          &info.reg_txfirst,     1);
    cc12xxSpiReadReg(CC120X_TXLAST,           &info.reg_txlast,      1);
    cc12xxSpiReadReg(CC120X_NUM_TXBYTES,      &info.reg_numtxbytes,  1);
    cc12xxSpiReadReg(CC120X_FIFO_NUM_TXBYTES, &info.reg_fifotxbytes, 1);

    //Store Values
    info.addr_first = info.reg_txfirst;
    info.addr_last  = info.reg_txlast;
    info.fill       = info.reg_numtxbytes;
    info.rem        = (info.reg_fifotxbytes && 0x0F) >> 0;

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_fifoCfgInfo cc12xx_get_fifoCfgInfo(void)
 *  @brief      get information on FIFO configuration from register map
 *
 *  @param      [out]   (cc12xx_fifoCfgInfo)    fifo
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      FIFO_CFG         - (0x001E) FIFO Configuration
 *          b7:b0        -      FIFO_THR - Threshold value for the RX and TX FIFO
 */
/************************************************************************************************************************************/
cc12xx_fifoCfgInfo cc12xx_get_fifoCfgInfo(void) {

    cc12xx_fifoCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_FIFO_CFG, &info.reg_fifocfg, 1);

    //Store Values
    info.fifo_thr = (info.reg_fifocfg & 0x7F) >> 0;

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_freqCfgInfo cc12xx_get_freqInfo(void)
 *  @brief      get vco & tx frequency configuration for radio
 *  @details    vco frequency is given by the FREQ value (u24) in FREQ2, FREQ1, and FREQ0 registers
 *
 *  @param      [out]   (cc12xx_freqCfgInfo)    freq config information
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section     Calculations
 *
 *       f_vco = (FREQ/2^16* + FREQOFF/2^18)*f_x_osc                (eq. 27)
 *
 *       f_rf  = f_vco / LO_DIV                                     (eq. 26)
 *
 *  @section    Register Description
 *      FREQ2            - (0x2F0C) Frequency Configuration [23:16]
 *      FREQ1            - (0x2F0D) Frequency Configuration [15:8]
 *      FREQ0            - (0x2F0E) Frequency Configuration [7:0]
 *      FS_CFG           - (0x0021) Frequency Synthesizer Configuration
 *          b3:b0 - FSD_BANDSELECT - Band select setting for LO divider
 *
 *  @section    LO Divider Configuration (@ref [4] Table 30)
 *      FSD_BS :  LO-Div : RF Band
 *      0010        4       820 - 960 MHz           <- used for Uhf-Id
 *      0100        8       410 - 480 MHz
 *      0110        12      273.3-320 MHz
 *      1000        16      205 - 240 MHz
 *      1010        20      164 - 192 MHz
 *      1011        24      136.7-160 MHz
 *
 *  @section    Opens
 *      FREQOFF0+1, FREQOFF_EST gives frequency offset for the freq
 *      FREQOFF_CFG configures the frequency offset
 *
 *  @src    [4] sec 9.12, Table 30
 *
 *  @note   RF Programming Resolution is a function of XOSC & RF Band, see [4] Table 31  for more information
 */
/************************************************************************************************************************************/
cc12xx_freqCfgInfo cc12xx_get_freqInfo(void) {

    cc12xx_freqCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_FREQ2,  &info.reg_freq2, 1);
    cc12xxSpiReadReg(CC120X_FREQ1,  &info.reg_freq1, 1);
    cc12xxSpiReadReg(CC120X_FREQ0,  &info.reg_freq0, 1);
    cc12xxSpiReadReg(CC120X_FS_CFG, &info.reg_fscfg, 1);

    //Store Values
    info.freq = ( ((uint32_t)info.reg_freq2) << 16)
              | ( ((uint32_t)info.reg_freq1) << 8)
              | ( ((uint32_t)info.reg_freq0) << 0);

    info.band_sel = (info.reg_fscfg & 0x0F);

    switch(info.band_sel) {
        case 2:
            info.lo_div = 4;
            break;
        case 4:
            info.lo_div = 8;
            break;
        case 6:
            info.lo_div = 12;
            break;
        case 8:
            info.lo_div = 16;
            break;
        case 10:
            info.lo_div = 20;
            break;
        case 11:
            info.lo_div = 24;
            break;
    }

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_freqSynthInfo cc12xx_get_freqSynthInfo(void)
 *  @brief      get the frequency synthesizer configuration
 *
 *  @param      [out]   (cc12xx_txFifoInfo)    freq synth info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      SETTLING_CFG     - (0x0020) Frequency Synthesizer Calibration and Settling Configuration
 *      FS_CFG           - (0x0021) Frequency Synthesizer Configuration
 *      FREQOFF_CFG      - (0x2F01) Frequency Offset Correction Configuration
 *      FS_DIG0          - (0x2F13) Frequency Synthesizer Digital Reg. 0
 *      FS_DIG1          - (0x2F12) Frequency Synthesizer Digital Reg. 1
 *      FS_CAL3          - (0x2F14) Frequency Synthesizer Calibration Reg. 3
 *      FS_CAL2          - (0x2F15) Frequency Synthesizer Calibration Reg. 2
 *      FS_CAL1          - (0x2F16) Frequency Synthesizer Calibration Reg. 1
 *      FS_CAL0          - (0x2F17) Frequency Synthesizer Calibration Reg. 0
 *      FS_CHP           - (0x2F18) Frequency Synthesizer Charge Pump Configuration
 *      FS_DIVTWO        - (0x2F19) Frequency Synthesizer Divide by 2
 *      FS_DSM1          - (0x2F1A) FS Digital Synthesizer Module Configuration Reg. 1
 *      FS_DSM0          - (0x2F1B) FS Digital Synthesizer Module Configuration Reg. 0
 *      FS_DVC1          - (0x2F1C) FS Digital Synthesizer Module Configuration Reg. 1
 *      FS_DVC0          - (0x2F1D) FS Digital Synthesizer Module Configuration Reg. 0
 *      FS_LBI           - (0x2F1E) Frequency Synthesizer Local Bias Configuration
 *      FS_PFD           - (0x2F1F) Frequency Synthesizer Phase Frequency Detector Configuration
 *      FS_PRE           - (0x2F20) Frequency Synthesizer Prescaler Configuration
 *      FS_REG_DIV_CML   - (0x2F21) Frequency Synthesizer Divider Regulator Configuration
 *      FS_SPARE         - (0x2F22) Frequency Synthesizer Spare
 *      FS_VCO4          - (0x2F23) FS Voltage Controlled Oscillator Configuration Reg. 4
 *      FS_VCO3          - (0x2F24) FS Voltage Controlled Oscillator Configuration Reg. 3
 *      FS_VCO2          - (0x2F25) FS Voltage Controlled Oscillator Configuration Reg. 2
 *      FS_VCO1          - (0x2F26) FS Voltage Controlled Oscillator Configuration Reg. 1
 *      FS_VCO0          - (0x2F27) FS Voltage Controlled Oscillator Configuration Reg. 0
 *      FSCAL_CTRL       - (0x2F8D) Frequency Synthesizer Calibration Control
 *      PHASE_ADJUST     - (0x2F8E) Frequency Synthesizer Phase Adjust
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_freqSynthInfo cc12xx_get_freqSynthInfo(void) {

    cc12xx_freqSynthInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_SETTLING_CFG,   &info.reg_settlecfg,   1);
    cc12xxSpiReadReg(CC120X_FS_CFG,         &info.reg_fsCfg,       1);
    cc12xxSpiReadReg(CC120X_FREQOFF_CFG,    &info.reg_freqoffscfg, 1);
    cc12xxSpiReadReg(CC120X_FS_DIG0,        &info.reg_dig0,        1);
    cc12xxSpiReadReg(CC120X_FS_DIG1,        &info.reg_dig1,        1);
    cc12xxSpiReadReg(CC120X_FS_CAL3,        &info.reg_cal3,        1);
    cc12xxSpiReadReg(CC120X_FS_CAL2,        &info.reg_cal2,        1);
    cc12xxSpiReadReg(CC120X_FS_CAL1,        &info.reg_cal1,        1);
    cc12xxSpiReadReg(CC120X_FS_CAL0,        &info.reg_cal0,        1);
    cc12xxSpiReadReg(CC120X_FS_CHP,         &info.reg_chp,         1);
    cc12xxSpiReadReg(CC120X_FS_DIVTWO,      &info.reg_divtwo,      1);
    cc12xxSpiReadReg(CC120X_FS_DSM1,        &info.reg_dsm1,        1);
    cc12xxSpiReadReg(CC120X_FS_DSM0,        &info.reg_dsm0,        1);
    cc12xxSpiReadReg(CC120X_FS_DVC1,        &info.reg_dvc1,        1);
    cc12xxSpiReadReg(CC120X_FS_DVC0,        &info.reg_dvc0,        1);
    cc12xxSpiReadReg(CC120X_FS_LBI,         &info.reg_lbi,         1);
    cc12xxSpiReadReg(CC120X_FS_PFD,         &info.reg_pfd,         1);
    cc12xxSpiReadReg(CC120X_FS_PRE,         &info.reg_pre,         1);
    cc12xxSpiReadReg(CC120X_FS_REG_DIV_CML, &info.reg_regdivcml,   1);
    cc12xxSpiReadReg(CC120X_FS_SPARE,       &info.reg_spare,       1);
    cc12xxSpiReadReg(CC120X_FS_VCO4,        &info.reg_vco4,        1);
    cc12xxSpiReadReg(CC120X_FS_VCO3,        &info.reg_vco3,        1);
    cc12xxSpiReadReg(CC120X_FS_VCO2,        &info.reg_vco2,        1);
    cc12xxSpiReadReg(CC120X_FS_VCO1,        &info.reg_vco1,        1);
    cc12xxSpiReadReg(CC120X_FS_VCO0,        &info.reg_vco0,        1);
    cc12xxSpiReadReg(CC120X_FSCAL_CTRL,     &info.reg_fscalctrl,   1);
    cc12xxSpiReadReg(CC120X_PHASE_ADJUST,   &info.reg_phaseadjust, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_paCfgInfo cc12xx_get_paCfgInfo(void)
 *  @brief      get information on Power Amplifier configuration from register map
 *
 *  @param      [out]   (cc12xx_paCfgInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      CC120X_PA_CFG3   - (0x2F39) Power Amplifier Configuration Reg. 3
 *      CC112X_PA_CFG2   - (0x002B) Power Amplifier Configuration Reg. 2
 *      CC120X_PA_CFG1   - (0x002C) Power Amplifier Configuration Reg. 1
 *      CC120X_PA_CFG0   - (0x002D) Power Amplifier Configuration Reg. 0
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_paCfgInfo cc12xx_get_paCfgInfo(void) {

    cc12xx_paCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_PA_CFG3, &info.reg_pacfg3, 1);
    cc12xxSpiReadReg(CC112X_PA_CFG2, &info.reg_pacfg2, 1);
    cc12xxSpiReadReg(CC120X_PA_CFG1, &info.reg_pacfg1, 1);
    cc12xxSpiReadReg(CC120X_PA_CFG0, &info.reg_pacfg0, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_extCtrlInfo cc12xx_get_extCtrlInfo(void)
 *  @brief      x
 *
 *  @param      [out]   (cc12xx_extCtrlInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      CC120X_EXT_CTRL   - (0x2F06) External Control Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_extCtrlInfo cc12xx_get_extCtrlInfo(void) {

    cc12xx_extCtrlInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_EXT_CTRL, &info.reg_extctrl, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_extClockInfo cc12xx_get_extClockInfo(void)
 *  @brief      ECG_CFG <-> 'External Clock' vocab
 *
 *  @param      [out]   (cc12xx_extClockInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      ECG_CFG   - (0x2F04) External Clock Frequency Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_extClockInfo cc12xx_get_extClockInfo(void) {

    cc12xx_extClockInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_ECG_CFG, &info.reg_ecgcfg, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_rfEndInfo cc12xx_get_rfEndInfo(void)
 *  @brief      return RF Front-end configuration
 *
 *  @param      [out]   (cc12xx_rfEndInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      RFEND_CFG1   - (0x0029) RFEND Configuration Reg. 1
 *      RFEND_CFG0   - (0x002A) RFEND Configuration Reg. 0
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_rfEndInfo cc12xx_get_rfEndInfo(void) {

    cc12xx_rfEndInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_RFEND_CFG1, &info.reg_rfendcfg1, 1);
    cc12xxSpiReadReg(CC120X_RFEND_CFG0, &info.reg_rfendcfg0, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_modemStatusInfo cc12xx_get_ModemStatusInfo(void)
 *  @brief      x
 *
 *  @param      [out]   (cc12xx_modemStatusInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      MODEM_STATUS1   - (0x2F92) Modem Status Reg. 1
 *      MODEM_STATUS0   - (0x2F93) Modem Status Reg. 0
 *      MDMCFG1         - (0x0012) General Modem Parameter Configuration Reg. 1
 *      MDMCFG0         - (0x0013) General Modem Parameter Configuration Reg. 0
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_modemStatusInfo cc12xx_get_ModemInfo(void) {

    cc12xx_modemStatusInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_MODEM_STATUS1, &info.reg_modemstatus1, 1);
    cc12xxSpiReadReg(CC120X_MODEM_STATUS0, &info.reg_modemstatus0, 1);
    cc12xxSpiReadReg(CC120X_MDMCFG1, &info.reg_modemConfig1, 1);
    cc12xxSpiReadReg(CC120X_MDMCFG0, &info.reg_modemConfig0, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_rngValInfo cc12xx_get_rngValInfo(void)
 *  @brief      get a random value
 *
 *  @param      [out]   (cc12xx_rngValInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      RNDGEN   - (0x2F80) Random Number Generator Value
 *
 *  @section    Reference ([4] Sec 9.10 - Random Number Generator)
 *      A random number generator is available and can be enabled by setting RNDGEN.RNDGEN_EN = 1. A random
 *      number can be read from RNDGEN.RNDGEN_VALUE in any state, but the number will be further randomized
 *      when in RX by XORing the feedback with receiver noise
 *
 *  @section    Opens
 *      Check if you should wait longer before reading RNG value
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_rngValInfo cc12xx_get_rngValInfo(void) {

    cc12xx_rngValInfo info;

    //Enable RNG
    uint8_t write_val = BIT7;
    cc12xxSpiWriteReg(CC120X_RNDGEN, &write_val, 1);

    //Read Registers
    cc12xxSpiReadReg(CC120X_RNDGEN, &info.reg_rndgen, 1);

    //Disable RNG
    write_val = 0x00;
    cc12xxSpiWriteReg(CC120X_RNDGEN, &write_val, 1);

    //Store Values
    info.rngVal = (info.reg_rndgen & 0x7F);                                 /* b6:b0                                                */

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_modCfgInfo cc12xx_get_modCfgInfo(void)
 *  @brief      Get the Tx Modulation Configuration
 *
 *  @param      [out]   (cc12xx_modCfgInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      MODCFG_DEV_E   - (0x000B) Modulation Format and Frequency Deviation Configuration
 *      DEVIATION_M    - (0x000A) Frequency Deviation Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_modCfgInfo cc12xx_get_modCfgInfo(void) {

    cc12xx_modCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_MODCFG_DEV_E, &info.reg_mod_e, 1);
    cc12xxSpiReadReg(CC120X_DEVIATION_M,  &info.reg_mod_m, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_symbolInfo cc12xx_get_symbolInfo(void)
 *  @brief      Get Symbol Rate Info
 *
 *  @param      [out]   (cc12xx_symbolInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      SYMBOL_RATE2   - (0x2F04) External Clock Frequency Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_symbolInfo cc12xx_get_symbolInfo(void) {

    cc12xx_symbolInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_SYMBOL_RATE2, &info.reg_symbolrate2, 1);
    cc12xxSpiReadReg(CC120X_SYMBOL_RATE1, &info.reg_symbolrate1, 1);
    cc12xxSpiReadReg(CC120X_SYMBOL_RATE0, &info.reg_symbolrate0, 1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_pktCfgInfo cc12xx_get_pktCfgInfo(void)
 *  @brief      ECG_CFG <-> 'External Clock' vocab
 *
 *  @param      [out]   (cc12xx_pktCfgInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      ECG_CFG   - (0x2F04) External Clock Frequency Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_pktCfgInfo cc12xx_get_pktCfgInfo(void) {

    cc12xx_pktCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_PKT_CFG2, &info.reg_pktCfg2, 1);
    cc12xxSpiReadReg(CC120X_PKT_CFG1, &info.reg_pktCfg1, 1);
    cc12xxSpiReadReg(CC120X_PKT_CFG0, &info.reg_pktCfg0, 1);
    cc12xxSpiReadReg(CC120X_PKT_LEN,  &info.reg_pktLen,  1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_gpioCfgInfo cc12xx_get_gpioCfgInfo(void)
 *  @brief      x
 *
 *  @param      [out]   (cc12xx_gpioCfgInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      ECG_CFG   - (0x2F04) External Clock Frequency Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_gpioCfgInfo cc12xx_get_gpioCfgInfo(void) {

    cc12xx_gpioCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_IOCFG3, &info.reg_gpio3, 1);
    cc12xxSpiReadReg(CC120X_IOCFG2, &info.reg_gpio2, 1);
    cc12xxSpiReadReg(CC120X_IOCFG1, &info.reg_gpio1, 1);
    cc12xxSpiReadReg(CC120X_IOCFG0, &info.reg_gpio0,  1);

    return info;
}


/************************************************************************************************************************************/
/** @fcn        cc12xx_xoscCfgInfo cc12xx_get_xoscCfgInfo(void)
 *  @brief      ECG_CFG <-> 'External Clock' vocab
 *
 *  @param      [out]   (cc12xx_xoscCfgInfo)    info
 *
 *  @pre        radio is initialized & ready for comm
 *
 *  @section    Register Description
 *      ECG_CFG   - (0x2F04) External Clock Frequency Configuration
 *
 *  @section    Opens
 *      Do processing and report values here
 */
/************************************************************************************************************************************/
cc12xx_xoscCfgInfo cc12xx_get_xoscCfgInfo(void) {

    cc12xx_xoscCfgInfo info;

    //Read Registers
    cc12xxSpiReadReg(CC120X_XOSC5, &info.reg_xosc5, 1);
    cc12xxSpiReadReg(CC120X_XOSC4, &info.reg_xosc4, 1);
    cc12xxSpiReadReg(CC120X_XOSC3, &info.reg_xosc3, 1);
    cc12xxSpiReadReg(CC120X_XOSC2, &info.reg_xosc2,  1);
    cc12xxSpiReadReg(CC120X_XOSC1, &info.reg_xosc1,  1);
    cc12xxSpiReadReg(CC120X_XOSC0, &info.reg_xosc0,  1);

    return info;
}

