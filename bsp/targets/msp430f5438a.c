/************************************************************************************************************************************/
/** @file       msp430f5438a.c
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
 *          clean headers for radio_spi() routines
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "msp430f5438a.h"


static uint16_t ui16IntState;


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_init(void) {

    //Watchdog (prevent timeout reset)
    WDTCTL = WDTPW | WDTHOLD;                                               /* Stop watchdog timer                                  */

    //Interrupts (disable global interrupts)
    ui16IntState = __get_interrupt_state();
    __disable_interrupt();

    return;
}



/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_enable_interrupts(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_enable_interrupts(void) {

    //Exit (return to previous interrupt state)
    __set_interrupt_state(ui16IntState);

    _BIS_SR(GIE);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_sleep(void)
 *  @brief      put the mcu to deep sleep
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_sleep(void) {

    _BIS_SR(LPM4_bits);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_clocks_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_clocks_init(void) {

    //  Set capacitor values for XT1, 32768 Hz */
//----------------------------------------------------------------------------------------------------------------------------------//
// @src     bspMcuStartXT1();
    // Set up XT1 Pins to analog function, and to lowest drive
    P7SEL |= 0x03;

    // Set internal cap values
    UCSCTL6 |= XCAP_3 ;

    // Check OFIFG fault flag
    while(SFRIFG1 & OFIFG) {
        // Check OFIFG fault flag
        while(SFRIFG1 & OFIFG) {
            // Clear OSC fault flags and OFIFG fault flag
            UCSCTL7 &= ~(DCOFFG + XT1LFOFFG + XT1HFOFFG + XT2OFFG);
            SFRIFG1 &= ~OFIFG;
        }

        // Reduce the drive strength
        UCSCTL6 &= ~(XT1DRIVE1_L + XT1DRIVE0);
    }


//----------------------------------------------------------------------------------------------------------------------------------//
// @src     bspSysClockSpeedSet(BSP_SYS_CLK_16MHZ);
    uint8_t ui8SetDcoRange, ui8SetVCore;
    uint32_t ui32SetMultiplier;

    const uint32_t ui32SystemClockSpeed = BSP_SYS_CLK_16MHZ;

    //
    // Set clocks (doing sanity check)
    // MCLK     = ui32SysClockSpeed;
    // SMCLK    = ui32SysClockSpeed;
    // ACLK     = 32 768 Hz
    //
    if((ui32SystemClockSpeed > 25000000UL) || (ui32SystemClockSpeed < 1000000UL)) {
        for(;;);
    }

    // Get DCO, VCore and multiplier settings for the given clock speed
    ui8SetDcoRange = DCORSEL_16MHZ;                                         /* <expanded>bspMcuGetSystemClockSettings(              */
    ui8SetVCore = VCORE_16MHZ;                                              /* ui32SystemClockSpeed, &ui8SetDcoRange, &ui8SetVCore, */
    ui32SetMultiplier = DCO_MULT_16MHZ;                                     /* &ui32SetMultiplier);                                 */

    // Set VCore setting
    msp430f5438a_bspMcuSetVCore(ui8SetVCore);

    // Disable FLL control loop, set lowest possible DCOx, MODx and select a suitable range
    __bis_SR_register(SCG0);
    UCSCTL0 = 0x00;
    UCSCTL1 = ui8SetDcoRange;

    // Set DCO multiplier and re-enable the FLL control loop
    UCSCTL2 = ui32SetMultiplier + FLLD_1;
    UCSCTL4 = SELA__XT1CLK | SELS__DCOCLKDIV  |  SELM__DCOCLKDIV ;
    __bic_SR_register(SCG0);

    // Loop until oscillator fault flags (XT1, XT2 & DCO fault flags) are cleared
    do {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);

        // Clear XT2, XT1, DCO fault flags
        SFRIFG1 &= ~OFIFG;
    }
    while(SFRIFG1 & OFIFG);

    // Worst-case settling time for the DCO
    __delay_cycles(781250);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_gpio_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_gpio_init(void) {

    //LED Pins
    P4OUT &= ~(BIT0+BIT1+BIT2+BIT3);
    P4SEL &= ~(BIT0+BIT1+BIT2+BIT3);
    P4DIR |= (BIT0+BIT1+BIT2+BIT3);

    //ACLK/MCLK/SMCLK out
    P11DIR |= (BIT0+BIT1+BIT2);                                             /* Enable output to P11.0/1/2                           */
    P11SEL |= (BIT0+BIT1+BIT2);                                             /* @note    I only validate ACLK & SMCLK out            */

    mcu_radio_gpio_init();

    P3SEL &= ~BIT0;                                                         /* RF_SPI0_CS_ as GPIO output high                      */
    P3OUT |=  BIT0;
    P3DIR |=  BIT0;

    //LED0
    P4OUT &= ~BIT0;                                                         /* LED0 On                                              */
    P4DIR |= BIT0;
    P4SEL &= ~BIT0;

    //DBG Pins
    P4OUT &= ~(BIT5|BIT6|BIT7);                                             /* Debug Pins                                           */
    P4DIR |= (BIT5|BIT6|BIT7);
    P4SEL &= ~(BIT5|BIT6|BIT7);

    return;
}



/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_timers_init(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void msp430f5438a_timers_init(void) {

    /*** Timer0_A Set-Up ***/
    TA0CCR0 |= 50000-1;
    TA0CCTL0 |= CCIE;
    TA0CTL |= TASSEL_1 + MC_1;

    return;
}

//----------------------------------------------------------------------------------------------------------------------------------//
//@src  cc12xx.h: #define TRXEM_SPI_BEGIN()              st( TRXEM_PORT_OUT &= ~TRXEM_SPI_SC_N_PIN; asm(" NOP"); )
void msp430f5438a_radio_spi_begin(void) {

    TRXEM_PORT_OUT &= ~TRXEM_SPI_SC_N_PIN;

    asm(" NOP");

    return;
}


//@src  cc12xx.h: #define TRXEM_SPI_TX(x)                st( UCB0IFG &= ~UCRXIFG; UCB0TXBUF= (x); )
void msp430f5438a_radio_spi_tx(uint8_t x) {

    UCB0IFG &= ~UCRXIFG;

    UCB0TXBUF= x;

    return;
}


//@src  cc12xx.h: #define TRXEM_SPI_WAIT_DONE()          st( while(!(UCB0IFG & UCRXIFG)); )
void msp430f5438a_radio_spi_wait_done(void) {

    while(!(UCB0IFG & UCRXIFG));

    return;
}


//@src  cc12xx.h: #define TRXEM_SPI_RX()                 UCB0RXBUF
uint8_t msp430f5438a_radio_spi_rx(void) {

    return UCB0RXBUF;
}


//@src  cc12xx.h: #define TRXEM_SPI_WAIT_MISO_LOW(x)     st( uint8_t count = 200;
//@note     no one uses this routine, keeping it around out of courtesy
void msp430f5438a_radio_spi_wait_miso_low(void) {

    uint8_t count = 200;
    //uint8_t x;                                                            /* unused input argument to source TI demo, omitting    */

    while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN) {
        __delay_cycles(5000);
        count--;
        if (count == 0) {
            break;
        }
    }

    //if(count>0) {
    //    x = 1;
    //} else {
    //    x = 0;
    //}

    return;
}


//@src  cc12xx.h: #define TRXEM_SPI_END()                st( asm(" NOP"); TRXEM_PORT_OUT |= TRXEM_SPI_SC_N_PIN; )
void msp430f5438a_radio_spi_end(void) {

    asm(" NOP");

    TRXEM_PORT_OUT |= TRXEM_SPI_SC_N_PIN;

    return;
}


//@src  manual generation
void msp430f5438a_radio_hw_reset(void) {

    int i;

    P8OUT &= ~BIT0;                                                         /* Apply Reset to the Module (1.120ms pulse)            */

    for(i=0; i<2000; i++) { asm(" NOP"); }

    P8OUT |= BIT0;

    return;
}

//@src  'trxSpiCmdStrobe(CC120X_SRES);'
void msp430f5438a_radio_sw_reset(void) {

    //Software Reset
    trxSpiCmdStrobe(CC120X_SRES);

    return;
}



//@src  cc12xx.h: 'while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);'
void msp430f5438a_radio_spi_wait_for_miso_low(void) {

    while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);

    return;
}


//@src  cc12xx.h: cc1175_spi_init()
void msp430f5438a_radio_spi_init(void) {


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

    return;
}


//@src  cc12xx.h: cc1175_gpio_init()
void msp430f5438a_radio_gpio_init(void) {

    //RESET_N
    P8OUT |= BIT0;                                                          /* RESET_N is active low, init to high                  */
    P8SEL &= ~BIT0;
    P8DIR |= BIT0;

    //CS_N
    P3SEL &= ~BIT0;
    P3OUT |=  BIT0;
    P3DIR |=  BIT0;


}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_bspMcuSetVCore(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void msp430f5438a_bspMcuSetVCore(uint8_t ui8Level) {

    uint8_t ui8ActLevel;

    do {
        ui8ActLevel = PMMCTL0_L & PMMCOREV_3;
        if(ui8ActLevel < ui8Level) {

            // Set Vcore (step by step)
            msp430f5438a_bspMcuSetVCoreUp(++ui8ActLevel);
        }
        if(ui8ActLevel > ui8Level) {
            // Set VCore step by step
            msp430f5438a_bspMcuSetVCoreDown(--ui8ActLevel);
        }
    } while(ui8ActLevel != ui8Level);
}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_bspMcuSetVCoreUp(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting.
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void msp430f5438a_bspMcuSetVCoreUp(uint8_t ui8Level) {
    // Open PMM module registers for write access
    PMMCTL0_H = 0xA5;

    // Set SVS/M high side to new ui8Level
    SVSMHCTL = (SVSMHCTL & ~(SVSHRVL0 * 3 + SVSMHRRL0)) | (SVSHE + SVSHRVL0 * ui8Level + SVMHE + SVSMHRRL0 * ui8Level);

    // Set SVM new Level
    SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * ui8Level;

    // Set SVS/M low side to new level
    SVSMLCTL = (SVSMLCTL & ~(SVSMLRRL_3)) | (SVMLE + SVSMLRRL0 * ui8Level);

    // Wait until SVM is settled
    while((PMMIFG & SVSMLDLYIFG) == 0);

    // Set VCore to 'level' and clear flags
    PMMCTL0_L = PMMCOREV0 * ui8Level;
    PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);

    if((PMMIFG & SVMLIFG)) {

        // Wait until level is reached
        while((PMMIFG & SVMLVLRIFG) == 0);
    }

    // Set SVS/M Low side to new level
    SVSMLCTL = (SVSMLCTL & ~(SVSLRVL0 * 3 + SVSMLRRL_3)) | (SVSLE + SVSLRVL0 * ui8Level + SVMLE + SVSMLRRL0 * ui8Level);

    // Lock PMM module registers from write access
    PMMCTL0_H = 0x00;
}


/************************************************************************************************************************************/
/** @fcn        void msp430f5438a_bspMcuSetVCoreDown(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting.
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void msp430f5438a_bspMcuSetVCoreDown(uint8_t ui8Level) {

    // Open PMM module registers for write access
    PMMCTL0_H = 0xA5;

    // Set SVS/M low side to new level
    SVSMLCTL = (SVSMLCTL & ~(SVSLRVL0 * 3 + SVSMLRRL_3)) | (SVSLRVL0 * ui8Level + SVMLE + SVSMLRRL0 * ui8Level);

    // Wait until SVM is settled
    while((PMMIFG & SVSMLDLYIFG) == 0);

    // Set VCore to new level
    PMMCTL0_L = (ui8Level * PMMCOREV0);

    // Lock PMM module registers for write access
    PMMCTL0_H = 0x00;
}


#ifdef TARGET_SEL_MSP430F5438A

/************************************************************************************************************************************/
/** @fcn        __interrupt void Timer0_A0 (void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0 (void) {

    P4OUT ^= BIT0;

    return;
}

#endif

