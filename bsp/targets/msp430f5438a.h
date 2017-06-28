#ifndef TARGETS_MSP430F5438A_H_
#define TARGETS_MSP430F5438A_H_

//Libraries
#include <stdint.h>


//Processor
#include <msp430.h>
#include "msp430f5438a_demo.h"


//Project
#include "../../globals.h"


//Radio
#include "../radio.h"


//Definitions
#define TRXEM_PORT_SEL          (P3SEL)
#define TRXEM_PORT_OUT          (P3OUT)
#define TRXEM_PORT_DIR          (P3DIR)
#define TRXEM_PORT_IN           (P3IN)

#define TRXEM_SPI_MOSI_PIN      (BIT1)
#define TRXEM_SPI_MISO_PIN      (BIT2)
#define TRXEM_SPI_SCLK_PIN      (BIT3)
#define TRXEM_SPI_SC_N_PIN      (BIT0)

#define DCO_MULT_16MHZ          488
#define DCORSEL_16MHZ           DCORSEL_5
#define VCORE_16MHZ             PMMCOREV_1
#define BSP_SYS_CLK_16MHZ       16000000UL


//Globals
extern void msp430f5438a_init(void);
extern void msp430f5438a_enable_interrupts(void);
extern void msp430f5438a_clocks_init(void);
extern void msp430f5438a_gpio_init(void);
extern void msp430f5438a_timers_init(void);

extern void msp430f5438a_radio_spi_begin(void);
extern void msp430f5438a_radio_spi_tx(uint8_t x);
extern void msp430f5438a_radio_spi_wait_done(void);
extern uint8_t msp430f5438a_radio_spi_rx(void);
extern void msp430f5438a_radio_spi_wait_miso_low(void);
extern void msp430f5438a_radio_spi_end(void);
extern void msp430f5438a_radio_hw_reset(void);
extern void msp430f5438a_radio_sw_reset(void);
extern void msp430f5438a_radio_spi_wait_for_miso_low(void);
extern void msp430f5438a_radio_spi_init(void);
extern void msp430f5438a_radio_gpio_init(void);


//Locals
extern void msp430f5438a_bspMcuSetVCore(uint8_t ui8Level);
extern void msp430f5438a_bspMcuSetVCoreUp(uint8_t ui8Level);
extern void msp430f5438a_bspMcuSetVCoreDown(uint8_t ui8Level);

#endif /* TARGETS_MSP430F5438A_H_ */

