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
 *          none current
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
    jmr_bspMcuSetVCore(ui8SetVCore);

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

    radio_gpio_init();

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
void msp430f5438a_radio_spi_begin(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_tx(uint8_t x) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_wait_done(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_rx(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_wait_miso_low(uint8_t x) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_end(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_hw_reset(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_wait_miso_high(uint8_t x) {
    for(;;);
    return;
}


void msp430f5438a_radio_spi_init(void) {
    for(;;);
    return;
}


void msp430f5438a_radio_gpio_init(void) {
    for(;;);
    return;
}

