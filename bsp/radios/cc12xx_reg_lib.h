#ifndef BSP_RADIOS_CC12XX_REG_LIB_H_
#define BSP_RADIOS_CC12XX_REG_LIB_H_


//Libraries
#include <stdint.h>


//Project
#include "cc12xx.h"


//Typedefs - Values
typedef enum {                                                              /*@ref [4] MARCSTATE.MARC_STATE - p.101                 */
    SLEEP          = 0b00000000,
    IDLE           = 0b00000001,
    XOFF           = 0b00000010,
    BIAS_SETTLE_MC = 0b00000011,
    REG_SETTLE_MC  = 0b00000100,
    MANCAL         = 0b00000101,
    BIAS_SETTLE    = 0b00000110,
    REG_SETTLE     = 0b00000111,
    STARTCAL       = 0b00001000,
    BWBOOST        = 0b00001001,
    FS_LOCK        = 0b00001010,
    IFADCON        = 0b00001011,
    ENDCAL         = 0b00001100,
    RX             = 0b00001101,
    RX_END         = 0b00001110,
    RSVD           = 0b00001111,
    TXRX_SWITCH    = 0b00010000,
    RX_FIFO_ERR    = 0b00010001,
    FSTXON         = 0b00010010,
    TX             = 0b00010011,
    TX_END         = 0b00010100,
    RXTX_SWITCH    = 0b00010101,
    TX_FIFO_ERR    = 0b00010110,
    IFADCON_TXRX   = 0b00010111
} marc_state_t;


//Typedefs - Info Reports

//MARC
typedef struct {
    uint8_t pinState;
    marc_state_t marcState;
    uint8_t marcStatus;

    uint8_t reg_marcspare;
    uint8_t reg_marcstate;
    uint8_t reg_marcstatus0;
    uint8_t reg_marcstatus1;
} cc12xx_marcInfo;


//Part Information
typedef struct  {
    uint8_t number;
    uint8_t version;

    uint8_t reg_partnumber;
    uint8_t reg_partversion;
} cc12xx_partInfo;


//TX FIFO
typedef struct {
    uint8_t addr_first;
    uint8_t addr_last;
    uint8_t fill;
    uint8_t rem;

    uint8_t reg_txfirst;
    uint8_t reg_txlast;
    uint8_t reg_numtxbytes;
    uint8_t reg_fifotxbytes;
} cc12xx_txFifoInfo;

//FIFO Config
typedef struct {
    uint8_t fifo_thr;

    uint8_t reg_fifocfg;
} cc12xx_fifoCfgInfo;

//Frequency Configuration
typedef struct {
    uint32_t freq;
    uint8_t band_sel;
    uint8_t lo_div;

    uint8_t reg_freq2;
    uint8_t reg_freq1;
    uint8_t reg_freq0;
    uint8_t reg_fscfg;
} cc12xx_freqCfgInfo;

// Frequency Synthesizer Config
typedef struct {
    uint8_t reg_settlecfg;
    uint8_t reg_fsCfg;
    uint8_t reg_freqoffscfg;
    uint8_t reg_dig1;
    uint8_t reg_dig0;
    uint8_t reg_cal3;
    uint8_t reg_cal2;
    uint8_t reg_cal1;
    uint8_t reg_cal0;
    uint8_t reg_chp;
    uint8_t reg_divtwo;
    uint8_t reg_dsm1;
    uint8_t reg_dsm0;
    uint8_t reg_dvc1;
    uint8_t reg_dvc0;
    uint8_t reg_lbi;
    uint8_t reg_pfd;
    uint8_t reg_pre;
    uint8_t reg_regdivcml;
    uint8_t reg_spare;
    uint8_t reg_vco4;
    uint8_t reg_vco3;
    uint8_t reg_vco2;
    uint8_t reg_vco1;
    uint8_t reg_vco0;
    uint8_t reg_fscalctrl;
    uint8_t reg_phaseadjust;
} cc12xx_freqSynthInfo;


typedef struct {
    uint8_t reg_pacfg3;
    uint8_t reg_pacfg2;
    uint8_t reg_pacfg1;
    uint8_t reg_pacfg0;
} cc12xx_paCfgInfo;


typedef struct {
    uint8_t reg_extctrl;
} cc12xx_extCtrlInfo;


typedef struct {
    uint8_t reg_ecgcfg;
} cc12xx_extClockInfo;


typedef struct {
    uint8_t reg_rfendcfg1;
    uint8_t reg_rfendcfg0;
} cc12xx_rfEndInfo;


typedef struct {
    uint8_t reg_modemstatus1;
    uint8_t reg_modemstatus0;
    uint8_t reg_modemConfig1;
    uint8_t reg_modemConfig0;
} cc12xx_modemStatusInfo;


typedef struct {
    uint8_t rngVal;

    uint8_t reg_rndgen;
} cc12xx_rngValInfo;


typedef struct {
    uint8_t reg_mod_e;
    uint8_t reg_mod_m;
} cc12xx_modCfgInfo;


typedef struct {
    uint8_t reg_symbolrate2;
    uint8_t reg_symbolrate1;
    uint8_t reg_symbolrate0;
} cc12xx_symbolInfo;


typedef struct {
    uint8_t reg_pktCfg2;
    uint8_t reg_pktCfg1;
    uint8_t reg_pktCfg0;
    uint8_t reg_pktLen;
} cc12xx_pktCfgInfo;


typedef struct {
    uint8_t reg_gpio3;
    uint8_t reg_gpio2;
    uint8_t reg_gpio1;
    uint8_t reg_gpio0;
} cc12xx_gpioCfgInfo;


typedef struct {
    uint8_t reg_xosc5;
    uint8_t reg_xosc4;
    uint8_t reg_xosc3;
    uint8_t reg_xosc2;
    uint8_t reg_xosc1;
    uint8_t reg_xosc0;
} cc12xx_xoscCfgInfo;


//Local


//Global
extern cc12xx_partInfo    cc12xx_get_partInfo(void);
extern cc12xx_marcInfo    cc12xx_get_marcInfo(void);
extern cc12xx_txFifoInfo  cc12xx_get_txFifoInfo(void);
extern cc12xx_fifoCfgInfo cc12xx_get_fifoCfgInfo(void);
extern cc12xx_freqCfgInfo cc12xx_get_freqInfo(void);
extern cc12xx_freqSynthInfo cc12xx_get_freqSynthInfo(void);
extern cc12xx_paCfgInfo cc12xx_get_paCfgInfo(void);
extern cc12xx_extCtrlInfo cc12xx_get_extCtrlInfo(void);
extern cc12xx_extClockInfo cc12xx_get_extClockInfo(void);
extern cc12xx_rfEndInfo cc12xx_get_rfEndInfo(void);
extern cc12xx_modemStatusInfo cc12xx_get_ModemInfo(void);
extern cc12xx_rngValInfo cc12xx_get_rngValInfo(void);
extern cc12xx_modCfgInfo cc12xx_get_modCfgInfo(void);
extern cc12xx_symbolInfo cc12xx_get_symbolInfo(void);
extern cc12xx_pktCfgInfo cc12xx_get_pktCfgInfo(void);
extern cc12xx_gpioCfgInfo cc12xx_get_gpioCfgInfo(void);
extern cc12xx_xoscCfgInfo cc12xx_get_xoscCfgInfo(void);

#endif /* BSP_RADIOS_CC12XX_REG_LIB_H_ */

