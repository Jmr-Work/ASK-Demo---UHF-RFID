/************************************************************************************************************************************/
/** @file       cc1175.c
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
 *          none current
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "cc1175.h"


/************************************************************************************************************************************/
/** @fcn        void cc1175_init(void)
 *  @brief      initialize the CC1175
 *  @details    x
 *
 *  @note    applies 1ms reset pulse to EMK
 *
 */
/************************************************************************************************************************************/
void cc1175_init(void) {

//<DIRECT COPY - cc1200_init()>
    uint8_t  marcState;
    uint32_t i;


    //******************************************************************************************************************************//
    //                                                          RESET                                                               //
    //******************************************************************************************************************************//
    //Hardware Reset
    P8OUT &= ~BIT0;                                                         /* Apply Reset to the Module (1.120ms pulse)            */
    for(i=0; i<2000; i++) { asm(" NOP"); }
    P8OUT |= BIT0;

    //Software Reset
    trxSpiCmdStrobe(CC112X_SRES);                                           /* CC1200 - CC120X_SRES                                 */

    //Verify ID
    bool valid_id = cc12xx_verifyPartNumber();

    if(!valid_id) {
        for(;;);                                                            /* not the CC1175, spin                                  */
    }


    //******************************************************************************************************************************//
    // INIT RADIO CONFIG                                                                                                            //
    //******************************************************************************************************************************//
    cc12xx_configure();                                                     /* configure the radio for use                          */


    //******************************************************************************************************************************//
    // CALIBRATE                                                                                                                    //
    //******************************************************************************************************************************//
    trxSpiCmdStrobe(CC112X_SCAL);                                           /* CC1200 - CC120X_SCAL                                 */

    // Wait for calibration to be done (radio back in IDLE state)
    do {
      cc120xSpiReadReg(CC112X_MARCSTATE, &marcState, 1);                    /* CC1200 - CC120X_MARCSTATE                            */
    } while (marcState != 0x41);

    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC112X_SPWD);                                           /* CC1200 - CC120X_SPWD                                 */

    return;
//</DIRECT COPY>
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_gpio_init(void)
 *  @brief      initialize the CC1200's GPIO for use
 *  @details    x
 */
/************************************************************************************************************************************/
void cc1175_gpio_init(void) {

    //RESET_N
    P8OUT |= BIT0;                                                          /* RESET_N is active low, init to high                  */
    P8SEL &= ~BIT0;
    P8DIR |= BIT0;

    //CS_N
    P3SEL &= ~BIT0;
    P3OUT |=  BIT0;
    P3DIR |=  BIT0;

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_spi_init(void)
 *  @brief      initialize the CC1175's SPI interface
 *  @details    x
 *
 * @src     direct copy trx_rf_spi.c:trxRfSpiInterfaceInit(0x10)
 *
 *  @param      [in]    (uint8) clockDivider - SMCLK/clockDivider gives SCLK frequency (0x10) <- <temp> 0x10
 *
 */
/************************************************************************************************************************************/
void cc1175_spi_init(void) {

//<DIRECT COPY - cc1200_run_init()>

    const uint8_t clockDivider = 0x10;                                      /* original value used in demo source                   */

    //******************************************************************************************************************************//
    //                                                  INIT UCB0 (SPI)                                                             //
    //******************************************************************************************************************************//
    // RF SPI0 CS as GPIO output high                                       /* (from bspInit() call) - config CS's GPIO             */
    P3SEL &= ~BIT0;
    P3OUT |=  BIT0;
    P3DIR |=  BIT0;

    /* Keep peripheral in reset state*/
    UCB0CTL1 |= UCSWRST;

    /* Configuration
     * -  8-bit
     * -  Master Mode
     * -  3-pin
     * -  synchronous mode
     * -  MSB first
     * -  Clock phase select = captured on first edge
     * -  Inactive state is low
     * -  SMCLK as clock source
     * -  Spi clk is adjusted corresponding to systemClock as the highest rate
     *    supported by the supported radios: this could be optimized and done
     *    after chip detect.
     */
    UCB0CTL0  =  0x00+UCMST + UCSYNC + UCMODE_0 + UCMSB + UCCKPH;
    UCB0CTL1 |=  UCSSEL_2;
    UCB0BR1   =  0x00;

    UCB0BR0 = clockDivider;

    /* Configure port and pins
     * - MISO/MOSI/SCLK GPIO controlled by peripheral
     * - CS_n GPIO controlled manually, set to 1
     */
    TRXEM_PORT_SEL |= TRXEM_SPI_MOSI_PIN + TRXEM_SPI_MISO_PIN + TRXEM_SPI_SCLK_PIN;
    TRXEM_PORT_SEL &= ~TRXEM_SPI_SC_N_PIN;
    TRXEM_PORT_OUT |= TRXEM_SPI_SC_N_PIN + TRXEM_SPI_MISO_PIN;/* Pullup on MISO */

    TRXEM_PORT_DIR |= TRXEM_SPI_SC_N_PIN;
    /* In case not automatically set */
    TRXEM_PORT_DIR |= TRXEM_SPI_MOSI_PIN + TRXEM_SPI_SCLK_PIN;
    TRXEM_PORT_DIR &= ~TRXEM_SPI_MISO_PIN;

    /* Release for operation */
    UCB0CTL1 &= ~UCSWRST;

//</DIRECT COPY>

}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_init(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_init(void) {

//<DIRECT COPY - cc1200_run_init()>
    //Empty FIFO before use (required)
    trxSpiCmdStrobe(CC112X_SFTX);                                           /* CC1200 - CC120X_SFTX                                 */

    // Strobe IDLE and fill TX FIFO
    trxSpiCmdStrobe(CC112X_SIDLE);                                          /* CC1200 - CC120X_SIDLE                                */

    // wait for radio to enter IDLE state
    while((trxSpiCmdStrobe(CC112X_SNOP)& 0xF0) != 0x00);                    /* CC1200 - CC120X_SNOP                                 */

    return;
//</DIRECT COPY>
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_loop(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_loop(void) {

//<DIRECT COPY - cc1200_run_loop()>
    //Load the buffer into the TX_FIFO
/*!?*/    cc112xSpiWriteTxFifo(tx_buff, TX_BUFF_SIZE);                      /* Send the message                                     */

    // Send packet
    trxSpiCmdStrobe(CC112X_STX);                                            /* CC1200 - CC120X_STX                                  */
//</DIRECT COPY>

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_waitForRoom(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_waitForRoom(void) {

//<DIRECT COPY - cc1200_run_waitForRoom()>
    uint16_t open_ct;

    // Wait for radio to finish sending packet
    do {
/*!?*/        open_ct = cc12xx_queryTxFifo();

        asm(" NOP");

    } while(open_ct < 120);
//</DIRECT COPY>

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1175_run_prepForNext(void)
 *  @brief      x
 */
/************************************************************************************************************************************/
void cc1175_run_prepForNext(void) {

//<DIRECT COPY - cc1200_run_prepForNext()>
    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC112X_SPWD);                                           /* CC1200 - CC120X_SPWD                                 */
//</DIRECT COPY>

    return;
}

