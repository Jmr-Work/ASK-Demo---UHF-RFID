/************************************************************************************************************************************/
/** @file       cc1175_simple_link_reg_config.c
 *  @brief      Register Configuration Values for CC1200
 *  @details    see docs/Config Generation Procedure.txt for generation procedure with TI SmartRF Studio 7
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
#include "cc1175_reg_config.h"


const registerSetting_t preferredSettings_cc1175[NUM_PREFERRED_SETTINGS_CC1175] =
{
 {CC112X_IOCFG3,            0xB0},                        //(0x0000) gpio3 io pin configuration
 {CC112X_IOCFG2,            0x06},                        //(0x0001) gpio2 io pin configuration
 {CC112X_IOCFG1,            0xB0},                        //(0x0002) gpio1 io pin configuration
 {CC112X_IOCFG0,            0x40},                        //(0x0003) gpio0 io pin configuration
 {CC112X_SYNC_CFG1,         0x0B},                        //(0x0008) sync word detection configuration reg. 1
 {CC112X_DEVIATION_M,       0x53},                        //(0x000a) frequency deviation configuration
 {CC112X_MODCFG_DEV_E,      0x1F},                        //(0x000b) modulation format and frequency deviation configur..
 {CC112X_DCFILT_CFG,        0x04},                        //(0x000c) digital dc removal configuration
 {CC112X_PREAMBLE_CFG1,     0x18},                        //(0x000d) preamble length configuration reg. 1
 {CC112X_FREQ_IF_CFG,       0x00},                        //(0x000f) rx mixer frequency configuration
 {CC112X_IQIC,              0x00},                        //(0x0010) digital image channel compensation configuration
 {CC112X_CHAN_BW,           0x01},                        //(0x0011) channel filter configuration
 {CC112X_MDMCFG0,           0x05},                        //(0x0013) general modem parameter configuration reg. 0
 {CC112X_SYMBOL_RATE2,      0xA4},                        //(0x0014) symbol rate configuration exponent and mantissa [1..
 {CC112X_SYMBOL_RATE1,      0x7A},                        //(0x0015) symbol rate configuration mantissa [15:8]
 {CC112X_SYMBOL_RATE0,      0xE1},                        //(0x0016) symbol rate configuration mantissa [7:0]
 {CC112X_AGC_REF,           0x3C},                        //(0x0017) agc reference level configuration
 {CC112X_AGC_CS_THR,        0xEC},                        //(0x0018) carrier sense threshold configuration
 {CC112X_AGC_CFG3,          0x83},                        //(0x001a) automatic gain control configuration reg. 3
 {CC112X_AGC_CFG2,          0x60},                        //(0x001b) automatic gain control configuration reg. 2
 {CC112X_AGC_CFG1,          0xA9},                        //(0x001c) automatic gain control configuration reg. 1
 {CC112X_AGC_CFG0,          0xC0},                        //(0x001d) automatic gain control configuration reg. 0
 {CC112X_FIFO_CFG,          0x00},                        //(0x001e) fifo configuration
 {CC112X_SETTLING_CFG,      0x03},                        //(0x0020) frequency synthesizer calibration and settling con..
 {CC112X_FS_CFG,            0x12},                        //(0x0021) frequency synthesizer configuration
 {CC112X_PKT_CFG0,          0x20},                        //(0x0028) packet configuration reg. 0
///      0b0100 0000 Continuous
//      0b0010 0000 Fixed
 {CC112X_PA_CFG0,           0x7A},                        //(0x002d) power amplifier configuration reg. 0
 {CC112X_PKT_LEN,           0xFF},                        //(0x002e) packet length configuration
//      255
 {CC112X_IF_MIX_CFG,        0x00},                        //(0x2f00) if mix configuration
 {CC112X_TOC_CFG,           0x0A},                        //(0x2f02) timing offset correction configuration
 {CC112X_FREQ2,             0x6C},                        //(0x2f0c) frequency configuration [23:16]
 {CC112X_FREQ1,             0x80},                        //(0x2f0d) frequency configuration [15:8]
 {CC112X_FREQ0,             0x00},                        //(0x2f0e) frequency configuration [7:0]
 {CC112X_FS_DIG1,           0x00},                        //(0x2f12) frequency synthesizer digital reg. 1
 {CC112X_FS_DIG0,           0x5F},                        //(0x2f13) frequency synthesizer digital reg. 0
 {CC112X_FS_CAL0,           0x0E},                        //(0x2f17) frequency synthesizer calibration reg. 0
 {CC112X_FS_DIVTWO,         0x03},                        //(0x2f19) frequency synthesizer divide by 2
 {CC112X_FS_DSM0,           0x33},                        //(0x2f1b) fs digital synthesizer module configuration reg. 0
 {CC112X_FS_DVC0,           0x17},                        //(0x2f1d) frequency synthesizer divider chain configuration ..
 {CC112X_FS_PFD,            0x50},                        //(0x2f1f) frequency synthesizer phase frequency detector con..
 {CC112X_FS_PRE,            0x6E},                        //(0x2f20) frequency synthesizer prescaler configuration
 {CC112X_FS_REG_DIV_CML,    0x14},                        //(0x2f21) frequency synthesizer divider regulator configurat..
 {CC112X_FS_SPARE,          0xAC},                        //(0x2f22) frequency synthesizer spare
 {CC112X_XOSC5,             0x0E},                        //(0x2f32) crystal oscillator configuration reg. 5
 {CC112X_XOSC3,             0xC7},                        //(0x2f34) crystal oscillator configuration reg. 3
 {CC112X_XOSC1,             0x07},                        //(0x2f36) crystal oscillator configuration reg. 1
 {CC112X_PARTNUMBER,        0x5A},                        //(0x2f8f) part number
 {CC112X_PARTVERSION,       0x21},                        //(0x2f90) part revision
 {CC112X_MODEM_STATUS1,     0x10},                        //(0x2f92) modem status reg. 1
};

