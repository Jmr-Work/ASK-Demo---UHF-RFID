/************************************************************************************************************************************/
/** @file       clocks.c
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
#include "clocks.h"


/************************************************************************************************************************************/
/** @fcn        void clocks_init(void)
 *  @brief      configure OSC & DCO
 *  @details    based from TrxEB reference 'per test'
 ************************************************************************************************************************************/
void clocks_init(void) {

#ifdef TARGET_SEL_MSP430F5438A
    msp430f5438a_clocks_init();
#endif

    return;
}


/************************************************************************************************************************************/
/** @fcn        void jmr_bspMcuSetVCore(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void jmr_bspMcuSetVCore(uint8_t ui8Level) {

    uint8_t ui8ActLevel;

    do {
        ui8ActLevel = PMMCTL0_L & PMMCOREV_3;
        if(ui8ActLevel < ui8Level) {

            // Set Vcore (step by step)
            jmr_bspMcuSetVCoreUp(++ui8ActLevel);
        }
        if(ui8ActLevel > ui8Level) {
            // Set VCore step by step
            jmr_bspMcuSetVCoreDown(--ui8ActLevel);
        }
    } while(ui8ActLevel != ui8Level);
}


/************************************************************************************************************************************/
/** @fcn        void jmr_bspMcuSetVCoreUp(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting.
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void jmr_bspMcuSetVCoreUp(uint8_t ui8Level) {
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
/** @fcn        void jmr_bspMcuSetVCoreDown(uint8_t ui8Level)
 *  @brief      This function sets the PMM core voltage (PMMCOREV) setting.
 *  @details    x
 *
 *  @param      [in]    (uint8_t ui8Level - the target VCore setting
 */
/************************************************************************************************************************************/
void jmr_bspMcuSetVCoreDown(uint8_t ui8Level) {

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

