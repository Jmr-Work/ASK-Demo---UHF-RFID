/************************************************************************************************************************************/
/** @file       radio_configure.c
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
#include "radio_configure.h"



/************************************************************************************************************************************/
/** @fcn        void radio_configure(void)
 *  @brief      configure the radio for use
 *
 *  @pre        radio was reset
 *  @post       radio is ready for operation
 */
/************************************************************************************************************************************/
void radio_configure(void) {

    uint16_t i;

    for(i=0; i<NUM_PREFERRED_SETTINGS_CC1200; i++) {

        uint8_t data = preferredSettings[i].data;

        uint16_t addr = preferredSettings[i].addr;

        radio_reg_write(addr, data);
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_reg_write(uint16_t addr, uint8_t data)
 *  @brief      apply register values to configure the radio for use
 *
 *  @param      [in]    (uint16_t) addr - address
 *  @param      [in]    (uint8_t) data  - data to write
 *
 */
/************************************************************************************************************************************/
void radio_reg_write(uint16_t addr, uint8_t data) {

    uint8_t rd[2];

    //Read
    cc120xSpiReadReg(addr, &rd[0], 1);

    //Write
    cc112xSpiWriteReg(addr, &data, 1);

    //Read
    cc120xSpiReadReg(addr, &rd[1], 1);

    //Validate
    if(data != rd[1]) {
        for(;;);                                                            /* catch & spin                                         */
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        void radio_reg_read(uint16_t addr, uint8_t *dataPtr)
 *  @brief      clean wrapper to read a single register value
 *
 *  @param      [in]    (uint16_t)  addr     - address
 *  @param      [in]    (uint8_t *) dataPtr  - where to store value
 *
 */
/************************************************************************************************************************************/
void radio_reg_read(uint16_t addr, uint8_t *dataPtr) {

    cc120xSpiReadReg(addr, dataPtr, 1);

    return;
}

