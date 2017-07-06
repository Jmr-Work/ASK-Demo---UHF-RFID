#ifndef TARGETS_CC2541_H_
#define TARGETS_CC2541_H_

//Project Definitions
#define chip    (2541)                                                      /* required for IAR headers                             */


//Libraries
#include <stdint.h>

//Processor
#include "ioCC2541.h"                   /* @src C:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\8051\inc\ioCC2541.h       */
#include "support/ioCC254x_bitdef.h"
#include "support/hal_types.h"

//Radio
#include "../radios/cc12xx.h"


//Definitions
#define BIT0                   (0x0001)
#define BIT1                   (0x0002)
#define BIT2                   (0x0004)
#define BIT3                   (0x0008)
#define BIT4                   (0x0010)
#define BIT5                   (0x0020)
#define BIT6                   (0x0040)
#define BIT7                   (0x0080)
#define BIT8                   (0x0100)
#define BIT9                   (0x0200)
#define BITA                   (0x0400)
#define BITB                   (0x0800)
#define BITC                   (0x1000)
#define BITD                   (0x2000)
#define BITE                   (0x4000)
#define BITF                   (0x8000)

//Radio Pins
#define RADIO_PORT              (P0)
#define RADIO_PORT_DIR          (P0DIR)
#define RADIO_PORT_SEL          (P0SEL)
#define RADIO_PIN_SCLK          (BIT5)
#define RADIO_PIN_MOSI          (BIT3)
#define RADIO_PIN_MISO          (BIT2)
#define RADIO_PIN_CS_N          (BIT4)

#define RADIO_RESET_PORT        (P1)
#define RADIO_RESET_PDIR        (P1DIR)
#define RADIO_RESET_PIN         (BIT2)

//SPI Config
#define SPI_BAUD_M              (0)                                         /* These values will give a baud rate of approx. 1.00   */
#define SPI_BAUD_E              (15)                                        /* Mbps at 32 MHz system clock                          */


//Globals
extern void cc2541_init(void);
extern void cc2541_clocks_init(void);
extern void cc2541_gpio_init(void);
extern void cc2541_timers_init(void);
extern void cc2541_enable_interrupts(void);

extern void cc2541_radio_spi_begin(void);
extern void cc2541_radio_spi_tx(uint8_t x);
extern void cc2541_radio_spi_wait_done(void);
extern uint8_t cc2541_radio_spi_rx(void);
extern void cc2541_radio_spi_wait_miso_low(void);
extern void cc2541_radio_spi_end(void);
extern void cc2541_radio_hw_reset(void);
extern void cc2541_radio_sw_reset(void);
extern void cc2541_radio_spi_wait_for_miso_low(void);
extern void cc2541_radio_spi_init(void);
extern void cc2541_radio_gpio_init(void);



#endif /* TARGETS_CC2541_CC2541_H_ */

