/************************************************************************************************************************************/
/** @file       cc2541.c
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
 *  @section    CC2541EMK Pinouts (using TrxEB)
 *      MOSI - P0.3     (P1.9)  / (TrxEB7.7)
 *      MISO - P0.2     (P1.7)  / (TrxEB7.9)
 *      SCLK - P0.5     (P2.18) / (TrxEB7.3)
 *      CS_N - P0.4     (P1.3)  / (TrxEB7.5)
 *      RST  - P1.2     (P2.17) / (TrxEB7.11)
 *
 *  @section    CC1175EMK Pinouts (using TrxEB)
 *      MOSI - MOSI     (P1.18) / (TrxEB-7.16)      Purple
 *      MISO - MISO     (P1.20) / (TrxEB-7.18)      Yellow
 *      SCLK - SCLK     (P1.16) / (TrxEB-7.12)      Green
 *      CS_N - CSN      (P1.14) / (TrxEB-7.14)      Blue
 *      RST  - RESET    (P1.15) / (TrxEB-7.10)      Grey
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
#include "cc2541.h"


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_begin(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_begin(void) {

    RADIO_PORT &= ~RADIO_PIN_CS_N;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_tx(void)
 *  @brief      transmit a byte over SPI0
 *  @details    x
 *
 *  @param      [in]    (uint8_t) value - 8-bit value to transmit, LSB
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_tx(uint8_t x) {

    // Write byte to USART0 buffer (transmit data)
    U0DBUF = x;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_wait_done(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_wait_done(void) {

    // Check if byte is transmitted
    while(!(U0CSR & U0CSR_TX_BYTE));

    // Clear transmit byte status
    U0CSR &= ~U0CSR_TX_BYTE;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_rx(void)
 *  @brief      return the value received last over SPI
 *  @details    immediate return no checks for completion
 */
/************************************************************************************************************************************/
uint8_t cc2541_radio_spi_rx(void) {
    return U0DBUF;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_wait_miso_low(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_wait_miso_low(void) {

    while(RADIO_PORT & RADIO_PIN_MISO);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_end(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_end(void) {

    RADIO_PORT |= RADIO_PIN_CS_N;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_hw_reset(void)
 *  @brief      manually apply 1ms HW reset pulse via the RESET_n pin
 *  @details    pulse is active low
 *
 *  @pre        GPIO enabled on reset pin & idle-high, clk @ 16 MHz
 *  @post       Radio HW reset has been performed, no verification
 */
/************************************************************************************************************************************/
void cc2541_radio_hw_reset(void) {

    int i;

    RADIO_RESET_PORT &= ~RADIO_RESET_PIN;                                   /* Apply Reset to the Module (1.000ms pulse)            */

    for(i=0; i<466; i++) { asm(" NOP"); }

    RADIO_RESET_PORT |= RADIO_RESET_PIN;
    
    for(i=0; i<466; i++) { asm(" NOP"); }                                   /* 1ms idle to settle before exit                       */

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_sw_reset(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_radio_sw_reset(void) {

    //Software Reset
    trxSpiCmdStrobe(CC120X_SRES);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_wait_for_miso_low(void)
 *  @brief      x
 *  @details    x
 * 
 *  @section    Opens
 *      Enable this!
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_wait_for_miso_low(void) {

    while(RADIO_PORT & RADIO_PIN_MISO);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_spi_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @post       USART0.SPI ready for use, CS_N(P0.4) idle-high
 */
/************************************************************************************************************************************/
void cc2541_radio_spi_init(void) {

    /**
     *  @brief   Set USART to SPI mode and Master mode
     *      - b7: 0 - SPI Mode
     *      - b5: 0 - Master
     */
    U0CSR = 0x00;


    /**
     * @brief   New
     *      - Set M&E (SPI_BAUD_M / SPI_BAUD_E)
     *      - Set U0GCR
     *          - Clock Polarity (CPOL:0)
     *          ? Clock Phase (CPHA:1)
     *          MSB Order (ORDER:1)
     *          BAUD_E
     */
    U0BAUD = SPI_BAUD_M;                                                    /* apply Mantissa [7:0]                                 */
    U0GCR =  U0GCR_ORDER | SPI_BAUD_E;

    //Set SSN
    RADIO_PORT |= RADIO_PIN_CS_N;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_radio_gpio_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @post       USART0.SPI-Alt1 GPIO ready for use
 */
/************************************************************************************************************************************/
void cc2541_radio_gpio_init(void) {

    // Configure USART0 for Alternative 1 => Port P0 (PERCFG.U0CFG = 0).
    PERCFG = (PERCFG & ~PERCFG_U0CFG) | PERCFG_U0CFG_ALT1;

    // Give priority to USART 0 over Timer 1 for port 0 pins.
    P2DIR &= P2DIR_PRIP0_USART0;

    // Set pins 2, 3 and 5 as peripheral I/O and pin 4 as GPIO output.
    RADIO_PORT_SEL = (RADIO_PORT_SEL & ~RADIO_PIN_CS_N) | RADIO_PIN_MOSI | RADIO_PIN_MOSI | RADIO_PIN_SCLK;
    RADIO_PORT_DIR |= RADIO_PIN_CS_N;

    //Enable RESET pin
    RADIO_RESET_PORT |= RADIO_RESET_PIN;                                    /* pre: high                                            */
    RADIO_RESET_PDIR |= RADIO_RESET_PIN;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Opens
 *      disable interrupts in this routine
 */
/************************************************************************************************************************************/
void cc2541_init(void) {
    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_enable_interrupts(void)
 *  @brief      x
 *  @details    x
 *
 *  @section    Opens
 *      enable interrupts in this routine
 */
/************************************************************************************************************************************/
void cc2541_enable_interrupts(void) {
    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_gpio_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @post       All GPIO input tri-state
 */
/************************************************************************************************************************************/
void cc2541_gpio_init(void) {
    
    //Inputs
    P0DIR = 0x00;
    P1DIR = 0x00;
    P2DIR = 0x00;
    
    //Tri-State
    P0INP = 0xFF;
    P1INP = 0xFF;
    P2INP = 0xFF;
    
    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_clocks_init(void)
 *  @brief      x
 *  @details    x
 *
 *  @post       Clock at Int. RCOSC @ 16 MHz
 *
 *  @section    Opens
 *      validate frequency selection
 *      find prettier #defs for this routine, it's bit-shifts are gross
 */
/************************************************************************************************************************************/
void cc2541_clocks_init(void) {
  
    /**
     * [b7]    OSC32K:  1 - D.C.
     * [b6]    OSC:     1 - 16MHz RCOSC
     * [b5:b3] TICKSPD: 001 - 16 MHz
     * [b2:b0] CLKSPD:  001 - 16 MHz
     *
     * @val     11001001
     */
    uint8_t clkoncmd_val = (1<<7) | (1<<6) | (0x01<<5) | (0x01<<0);
  
    //Apply Value
    CLKCONCMD = clkoncmd_val;
  
    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc2541_timers_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_timers_init(void) {
    return;
}

