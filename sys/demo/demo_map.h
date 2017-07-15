#ifndef SYS_DEMO_DEMO_MAP_H_
#define SYS_DEMO_DEMO_MAP_H_


//Project Configuration
//#define DEMO_MAP_USES_CC2541
#define DEMO_MAP_USES_MSP430F5438A


#ifdef DEMO_MAP_USES_CC2541
    #define chip        (2541)
#endif


//Libraries
#include <stdint.h>
#include <stdio.h>


//Processor
#include "../../bsp/mcu.h"


//Project
#include "../../globals.h"


//Radio
#include "../../bsp/radio.h"



//Definitions
// Define size of allocated UART RX/TX buffer (just an example).
#define SIZE_OF_UART_TX_BUFFER   (50)

// UART test characters.
#define UART_TEST_DATA "Texas Instruments LPRF!"

// Test definitions.
//#define UART_TST_MODE_RX
#define UART_TST_MODE_TX

// Baudrate = 57.6 kbps (U0BAUD.BAUD_M = 216, U0GCR.BAUD_E = 10), given 32 MHz system clock.
#define UART_BAUD_M  216
#define UART_BAUD_E  10


//Globals
extern void demo_map(void);


//Locals
static void usart1_init(void);
static void uart1_send(uint8_t* uartTxBuf, uint16_t uartTxBufLength);
static void print_register(uint8_t *name, uint16_t address, uint8_t value);
static void jmr_sprintf_u8(uint8_t *dest, uint8_t value);
static void jmr_sprintf_u16(uint8_t *dest, uint16_t value);
static char get_char(uint8_t num);
static void read_map_to_console(void);


////Vars
//extern const char cc1200_names[NUM_PREFERRED_SETTINGS_CC1200][20];
//static void uart0Receive(void);

#endif /* SYS_DEMO_DEMO_MAP_H_ */

