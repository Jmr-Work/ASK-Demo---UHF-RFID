/************************************************************************************************************************************/
/** @file       demo_map.c
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
 *          x
 *
 *  @section    Status
 *          this code is functional but held at this time and not needed. If interested in the future this should be easy to extend
 *          to full functional use
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "demo_map.h"


/************************************************************************************************************************************/
/** @fcn        void demo_map(void)
 *  @brief      read the map to an open serial
 *  @details    x
 *
 */
/************************************************************************************************************************************/
void demo_map(void) {

    //Init Serial
    usart1_init();

    //Read-out Map
    uart1_send("\n\rRadio Register Map:\n\r", 23);
    read_map_to_console();                                                  /* read entire map                                      */

    //Exit
    mcu_sleep();
}


/************************************************************************************************************************************/
/** @fcn        static void read_map_to_console(void)
 *  @brief      read the map out to console
 *  @details    x
 *
 *  @pre        USART1.SPI ready
 *
 *  @param      [in] (uint8_t *) name - name to display
 *  @param      [in] (uint16_t)  address - address in register map
 *  @param      [in] (uint8_t)   value - value of register
 */
/************************************************************************************************************************************/
static void read_map_to_console(void) {

    uint16_t i;
    uint8_t  read_val;

    for(i=0; i<NUM_PREFERRED_SETTINGS; i++) {

        uint16_t addr = preferredSettings[i].addr;

        cc12xxSpiReadReg(addr, (uint8_t *) &read_val, 1);

        print_register((uint8_t *) radio_reg_names[i], addr, read_val);

        asm(" NOP");
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        static void print_register(uint8_t *name, uint16_t address, uint8_t value)
 *  @brief      print a register to the console
 *  @details    x
 *
 *  @pre        USART1.SPI ready
 *
 *  @param      [in] (uint8_t *) name - name to display
 *  @param      [in] (uint16_t)  address - address in register map
 *  @param      [in] (uint8_t)   value - value of register
 */
/************************************************************************************************************************************/
static void print_register(uint8_t *name, uint16_t address, uint8_t value) {

  uint8_t addr_buff[10], val_buff[10];

  //Prep
  jmr_sprintf_u16(addr_buff, address);
  jmr_sprintf_u8(val_buff, value);


  //Send
  uart1_send(name, strlen((char const *) name));
  uart1_send("(", 1);
  uart1_send(addr_buff, strlen((char const *) addr_buff));
  uart1_send("): ", 3);
  uart1_send(val_buff, strlen((char const *) val_buff));
  uart1_send("\n\r", 2);

  return;
}


/************************************************************************************************************************************/
/** @fcn        static void jmr_sprintf_u8(uint8_t *dest, uint8_t value)
 *  @brief      print a 8-bit value to dest in hexadecimal
 *  @details    x
 *
 *  @param      [in] (uint8_t *) dest - storage location for string
 *  @param      [in] (uin86_t) value - number to parse & store
 */
/************************************************************************************************************************************/
static void jmr_sprintf_u8(uint8_t *dest, uint8_t value) {

    int chars[2];

    //Calc the Digits
    chars[0] = (value>>4) & 0x0F;
    chars[1] = (value>>0) & 0x0F;

    //Store the Digits
    dest[0] = '0';
    dest[1] = 'x';
    dest[2] = get_char(chars[0]);
    dest[3] = get_char(chars[1]);
    dest[4] = 0x00;                                                         /* EOString                                             */

    return;
}


/************************************************************************************************************************************/
/** @fcn        static void jmr_sprintf_u16(uint8_t *dest, uint16_t value)
 *  @brief      print a 16-bit value to dest in hexadecimal
 *  @details    x
 *
 *  @param      [in] (uint8_t *) dest - storage location for string
 *  @param      [in] (uint16_t) value - number to parse & store
 */
/************************************************************************************************************************************/
static void jmr_sprintf_u16(uint8_t *dest, uint16_t value) {

    int chars[4];

    //Calc the Digits
    chars[0] = (value>>12) & 0x0F;
    chars[1] = (value>>8) & 0x0F;
    chars[2] = (value>>4) & 0x0F;
    chars[3] = (value>>0) & 0x0F;

    //Store the Digits
    dest[0] = '0';
    dest[1] = 'x';
    dest[2] = get_char(chars[0]);
    dest[3] = get_char(chars[1]);
    dest[4] = get_char(chars[2]);
    dest[5] = get_char(chars[3]);
    dest[6] = 0x00;

    return;
}

/************************************************************************************************************************************/
/** @fcn        static char get_char(uint8_t num)
 *  @brief      get a character for the input number
 *  @details    e.g. return '1' for an input of 1
 *
 *  @param      [in] (uint8_t) num - number
 *
 *  @return     (char) character representation of num
 */
/************************************************************************************************************************************/
static char get_char(uint8_t num) {

  char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  return chars[num];
}


/************************************************************************************************************************************/
/** @fcn        static void usart1_init(void)
 *  @brief      initialize USART1 in SPI mode at 57.600 kHz
 *  @details    USART0.SPI-Alt1
 *
 *  @note       this USART selection does not overlap with existing IO & periph usage
 *
 *  @section    USART1.SPI Alternative 2 Configuration
 *                  MOSI   : P1_6  (RF1.18) (P7.16) 'SPI0_MOSI'
 *                  MISO   : P1_7
 *                  SCLK   : P1_5
 *                  SS     : P1_4
 *
 *  @section    <prev> USART0.SPI Alternative 1 Configuration
 *                  MISO   : P0_2
 *                  MOSI   : P0_3 (RF1.9) (P7.7) 'SPI1_MOSI'
 *                  SCLK   : P0_5
 *                  SS     : P0_4
 *
 *  @src        uart_cc254x.eww/uart_poll_cc254x.ewp:uart_poll.c
 *  @src        msp430x54xA_uscia0_uart_01.c (Using A0TXD - P3.4, A0RXD - P3.5 )
 *
 */
/************************************************************************************************************************************/
static void usart1_init(void) {

#ifdef DEMO_MAP_USES_CC2541
    //--------------------------------------------------------Clock setup-----------------------------------------------------------//
    //(See basic software example "clk_xosc_cc254x")

    // Set system clock source to HS XOSC, with no pre-scaling
    CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;

    // Wait until clock source has changed
    while (CLKCONSTA & CLKCON_OSC);


    //--------------------------------------------------------Setup I/O ports-------------------------------------------------------//
    // Configure USART1 for Alternative 2 => Port P1 (PERCFG.U1CFG = 1)
    PERCFG = (PERCFG & ~PERCFG_U1CFG) | PERCFG_U1CFG_ALT2;


    //Give priority to USART 1 over XYZ for port abc pins
    P2SEL |= P2SEL_PRI3P1;                                                  /* USART1 has priority over USART0                      */
    P2SEL &= ~P2SEL_PRI2P1;                                                 /* USART1 has priority over Timer3                      */

    // Set pin6 as GPIO output
    P1SEL |= BIT6 + BIT7;                                                   /* Rx&Tx only                                           */

    //Configure UART

    // Initialize bitrate = 57.6 kbps
    U1BAUD = UART_BAUD_M;
    U1GCR = (U1GCR & ~U1GCR_BAUD_E) | UART_BAUD_E;


    // Initialize UART protocol (start/stop bit, data bits, parity, etc.):
    // USART mode = UART (U1CSR.MODE = 1)
    U1CSR |= U1CSR_MODE;

    // Start bit level = low => Idle level = high  (U1UCR.START = 0)
    U1UCR &= ~U1UCR_START;

    // Stop bit level = high (U1UCR.STOP = 1)
    U1UCR |= U1UCR_STOP;

    // Number of stop bits = 1 (U1UCR.SPB = 0)
    U1UCR &= ~U1UCR_SPB;

    // Parity = disabled (U0UCR.PARITY = 0)
    U1UCR &= ~U1UCR_PARITY;

    // 9-bit data enable = 8 bits transfer (U0UCR.BIT9 = 0)
    U1UCR &= ~U1UCR_BIT9;

    // Level of bit 9 = 0 (U0UCR.D9 = 0), used when U0UCR.BIT9 = 1
    // Level of bit 9 = 1 (U0UCR.D9 = 1), used when U0UCR.BIT9 = 1
    // Parity = Even (U0UCR.D9 = 0), used when U0UCR.PARITY = 1
    // Parity = Odd (U0UCR.D9 = 1), used when U0UCR.PARITY = 1
    U1UCR &= ~U1UCR_D9;

    // Flow control = disabled (U0UCR.FLOW = 0)
    U1UCR &= ~U1UCR_FLOW;

    // Bit order = LSB first (U0GCR.ORDER = 0)
    U1GCR &= ~U1GCR_ORDER;
#else
    /**
     * @wiring      TXD: P3.4(P7.9), RXD: P3.5(P7.7)
     */
    P3SEL |= 0x30;                                                           /* P3.4,5 = USCI_A0 TXD/RXD (TrxEB P7.9/P7.7)           */
    UCA0CTL1 |= UCSWRST;                                                    /* **Put state machine in reset**                       */
    UCA0CTL1 |= UCSSEL_2;                                                   /* SMCLK                                                */
    UCA0BR0 = 140;                                                          /* 115200 (see User's Guide)                            */
    UCA0BR1 = 0;                                                            /* 115200                                               */
    UCA0MCTL |= UCBRS_1 + UCBRF_0;                                          /* Modulation UCBRSx=1, UCBRFx=0                        */
    UCA0CTL1 &= ~UCSWRST;                                                   /* **Initialize USCI state machine**                    */
    //UCA0IE |= UCRXIE;                                                     /* Enable USCI_A0 RX interrupt                          */
#endif

    return;
}


/************************************************************************************************************************************/
/** @fcn        void uart1_send(uint8_t* uartTxBuf, uint16_t uartTxBufLength)
 *  @brief      tx a char array
 *  @details    Function which sends a requested number of bytes on UART0
 *
 *  @param      [in] (uint8_t *) uartTxBuf - data to send
 *  @param      [in] (uint16_t)  uartTxBufLength - number to send
 *
 *  @src        uart_cc254x.eww/uart_poll_cc254x.ewp:uart_poll.c:257
 */
/************************************************************************************************************************************/
static void uart1_send(uint8_t* uartTxBuf, uint16_t uartTxBufLength) {

    uint16_t uartTxIndex;

#ifdef DEMO_MAP_USES_CC2541

    // Clear any pending TX interrupt request (set U0CSR.TX_BYTE = 0)
    U1CSR &= ~U1CSR_TX_BYTE;

    // Loop: send each UART0 sample on the UART0 TX line
    for (uartTxIndex = 0; uartTxIndex < uartTxBufLength; uartTxIndex++) {

        U1DBUF = uartTxBuf[uartTxIndex];

        while(!(U1CSR & U1CSR_TX_BYTE));

        U1CSR &= ~U1CSR_TX_BYTE;
    }
#else

    // Loop: send each UART0 sample on the UART0 TX line
    for (uartTxIndex = 0; uartTxIndex < uartTxBufLength; uartTxIndex++) {

        UCA0TXBUF = uartTxBuf[uartTxIndex];

        while(UCA0STAT & UCBUSY);

        UCA0IFG &= ~ UCTXIFG;
    }
#endif


    return;
}


/************************************************************************************************************************************/
/** @fcn        static void uart0Receive(void)
 *  @brief      rx a char on USART1.UART & echo back
 *  @details    x
 *
 *  @src        uart_cc254x.eww/uart_poll_cc254x.ewp:uart_poll.c:
 */
/************************************************************************************************************************************/
//static void uart0Receive(void) {
//
//    uint8_t rx_buff[3];
//
//#ifdef DEMO_MAP_USES_CC2541
//    // Enable UART0 RX (U0CSR.RE = 1)
//    U1CSR |= U1CSR_RE;
//
//    // Clear any pending RX interrupt request (set U0CSR.RX_BYTE = 0)
//    U1CSR &= ~U1CSR_RX_BYTE;
//
//    // Wait until data received (U0CSR.RX_BYTE = 1)
//    while( !(U1CSR & U1CSR_RX_BYTE) );
//
//    rx_buff[0] = U1DBUF;
//#else
//    //Wait for Rx Char
//    while(!(UCA0IFG & UCRXIFG));
//
//    //Load into buf
//    rx_buff[0] = UCA0RXBUF;
//
//#endif
//
//    uart1_send("Byte Received: '", 16);
//    uart1_send(&rx_buff[0], 1);
//    uart1_send("'\n\r", 3);
//
//    return;
//}

