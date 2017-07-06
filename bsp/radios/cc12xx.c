/************************************************************************************************************************************/
/** @file       cc12xx.c
 *  @brief      library for Uhf-Id control of the CC1200 & CC1175
 *  @details    this is the working configuration & control code developed by Justin for CC1200 use. This is targeted for extension
 *              to use with the CC1175 but has not been yet verified
 *
 *  @supported  CC1200
 *  @open       CC1175
 *
 *  @vocab
 *          The vocabulary 'cc12xx' here denotes this library, not the TI part family (e.g. CC1200)
 *
 *  @section    Unverified Routines
 *          All
 *
 *  @section    Verified Routines
 *          x
 *
 *  @section    Opens
 *          x
 *
 *  @target     MSP430F5438A/CC2541/MSP430F5529
 *  @board      TrxEB/CC2541EMK/5529-Launchpad
 *
 *  @author     Justin Reina, Firmware Engineer, Misc. Company
 *  @created    6/21/17
 *  @last rev   x
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "cc12xx.h"


/************************************************************************************************************************************/
/** @fcn        rfStatus_t trxSpiCmdStrobe(uint8_t cmd)
 *  @brief      Send command strobe to the radio
 *  @details    Validation of provided is not done. Function assumes chip is ready
 *
 *  @param      [in]   (uint8_t) cmd - command strobe
 *  @param      [out]  (uint8_t) Returns status byte read during transfer of command strobe
 */
/************************************************************************************************************************************/
rfStatus_t trxSpiCmdStrobe(uint8_t cmd) {

    uint8_t rc;

    mcu_radio_spi_begin();

    mcu_radio_spi_wait_for_miso_low();

    mcu_radio_spi_tx(cmd);

    mcu_radio_spi_wait_done();

    rc = mcu_radio_spi_rx();

    mcu_radio_spi_end();

    return(rc);
}

/************************************************************************************************************************************/
/** @fcn        rfStatus_t cc12xxSpiReadReg(uint16_t addr, uint8_t *pData, uint8_t len)
 *  @brief      read value(s) from config/status/extended radio register(s)
 *              - If len  = 1: Reads a single register
 *              - if len != 1: Reads len register values in burst mode
 *
 *  @param      [in] (uint16_t)  addr  - address of first register to read
 *  @param      [in] (uint8_t *) pData - pointer to data array where read bytes are saved
 *  @param      [in] (uint8_t)   len   - number of bytes to read
 *
 *  @return     rfStatus_t
 */
/************************************************************************************************************************************/
rfStatus_t cc12xxSpiReadReg(uint16_t addr, uint8_t *pData, uint8_t len) {

  uint8_t tempExt  = (uint8_t)(addr>>8);
  uint8_t tempAddr = (uint8_t)(addr & 0x00FF);
  uint8_t rc;


  /* Checking if this is a FIFO access -> returns chip not ready  */
  if((CC120X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) {
      return STATUS_CHIP_RDYn_BM;
  }

  /* Decide what register space is accessed */
  if(!tempExt) {
      rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS), tempAddr, pData, len);
  }
  else if (tempExt == 0x2F) {
      rc = trx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS), tempExt, tempAddr, pData, len);
  }
  return (rc);
}


/************************************************************************************************************************************/
/** @fcn        rfStatus_t cc112xSpiWriteReg(uint16_t addr, uint8_t*pData, uint8_t len)
 *  @brief      Write value(s) to config/status/extended radio register(s).
 *              If len  = 1: Writes a single register
 *              if len  > 1: Writes len register values in burst mode
 *
 *  @param      addr   - address of first register to write
 *  @param      *pData - pointer to data array that holds bytes to be written
 *  @param      len    - number of bytes to write
 *
 *  @return     rfStatus_t
 */
/************************************************************************************************************************************/
rfStatus_t cc112xSpiWriteReg(uint16_t addr, uint8_t*pData, uint8_t len) {

    uint8_t tempExt  = (uint8_t)(addr>>8);
    uint8_t tempAddr = (uint8_t)(addr & 0x00FF);
    uint8_t rc;

    /* Checking if this is a FIFO access - returns chip not ready */
    if((CC112X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

    /* Decide what register space is accessed */
    if(!tempExt) {
        rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS), tempAddr, pData, len);
    }
    else if (tempExt == 0x2F) {
        rc = trx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS), tempExt, tempAddr, pData, len);
    }

    return (rc);
}


/************************************************************************************************************************************/
/** @fcn        rfStatus_t cc112xSpiWriteTxFifo(uint8 *pData, uint8 len)
 *  @brief       Write pData to radio transmit FIFO.
 *
 *  @param       *pData - pointer to data array that is written to TX FIFO
 *  @param       len    - Length of data array to be written
 *
 *  @return      rfStatus_t
 */
/************************************************************************************************************************************/
rfStatus_t cc112xSpiWriteTxFifo(uint8_t *pData, uint8_t len) {

    uint8_t rc;

    rc = trx8BitRegAccess(0x00,CC112X_BURST_TXFIFO, pData, len);

    return (rc);
}


/************************************************************************************************************************************/
/** @fcn        uint8_t cc12xx_queryTxFifo(void)
 *  @brief      query the TX FIFO for #elements open for insertion
 *
 *  @pre        TX FIFO is initialized
 *
 *  @return     (uint32_t) open count
 */
/************************************************************************************************************************************/
uint8_t cc12xx_queryTxFifo(void) {

    uint8_t fill_ct, open_ct;

    cc12xxSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct, 1);

    if(fill_ct < 128) {
        open_ct = 127 - fill_ct;
    } else {
        open_ct = 0;
    }

    return open_ct;
}


/************************************************************************************************************************************/
/** @fcn        void cc12xx_configure(void)
 *  @brief      configure the radio for use
 *
 *  @pre        radio was reset
 *  @post       radio is ready for operation
 */
/************************************************************************************************************************************/
void cc12xx_configure(void) {

    uint16_t i;

    for(i=0; i<NUM_PREFERRED_SETTINGS_CC1200; i++) {

        uint8_t data = preferredSettings[i].data;

        uint16_t addr = preferredSettings[i].addr;

        cc12xx_reg_write(addr, data);
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc12xx_reg_write(uint16_t addr, uint8_t data)
 *  @brief      apply register values to configure the radio for use
 *
 *  @param      [in]    (uint16_t) addr - address
 *  @param      [in]    (uint8_t) data  - data to write
 *
 */
/************************************************************************************************************************************/
void cc12xx_reg_write(uint16_t addr, uint8_t data) {

    uint8_t rd[2];

    //Read
    cc12xxSpiReadReg(addr, &rd[0], 1);

    //Write
    cc112xSpiWriteReg(addr, &data, 1);

    //Read
    cc12xxSpiReadReg(addr, &rd[1], 1);

    //Validate
    if(data != rd[1]) {
        for(;;);                                                            /* catch & spin                                         */
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc12xx_reg_read(uint16_t addr, uint8_t *dataPtr)
 *  @brief      clean wrapper to read a single register value
 *
 *  @param      [in]    (uint16_t)  addr     - address
 *  @param      [in]    (uint8_t *) dataPtr  - where to store value
 *
 */
/************************************************************************************************************************************/
void cc12xx_reg_read(uint16_t addr, uint8_t *dataPtr) {

    cc12xxSpiReadReg(addr, dataPtr, 1);

    return;
}


/************************************************************************************************************************************/
/** @fcn        bool cc1200_verifyPartNumber(void)
 *  @brief      is the register value for [PARTNUMBER] match the CC1200?
 *
 *  @return     (bool) if Part Number is valid for CC1200
 */
/************************************************************************************************************************************/
bool cc12xx_verifyPartNumber(void) {

    uint16_t i;

    uint8_t part_number;

    //small reset delay, cc12xx is non-deterministic on Reg-read values immediately after reset
    for(i=0; i<1000; i++) {
        asm(" NOP");
    }

    //Check Part Number
    cc12xxSpiReadReg(CC120X_PARTNUMBER, &part_number, 1);

    return (part_number == CHIP_PARTNUMBER_UHF_ID);
}


/************************************************************************************************************************************/
/** @fcn        rfStatus_t trx8BitRegAccess(uint8 accessType, uint8 addrByte, uint8 *pData, uint16 len)
 *  @brief      This function performs a read or write from/to a 8bit register address space. The function handles
 *              burst and single read/write as specified in addrByte. Function assumes that chip is ready. input parameters
 *  @details    x
 *
 * @param       accessType - Specifies if this is a read or write and if it's
 *                           a single or burst access. Bitmask made up of
 *                           RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/
 *                           RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 * @param       addrByte - address byte of register.
 * @param       pData    - data array
 * @param       len      - Length of array to be read(TX)/written(RX)
 *
 * @return      chip status
 */
/************************************************************************************************************************************/
rfStatus_t trx8BitRegAccess(uint8_t accessType, uint8_t addrByte, uint8_t *pData, uint16_t len) {

    uint8_t readValue;

    /* Pull CS_N low and wait for SO to go low before communication starts */
    mcu_radio_spi_begin();
    mcu_radio_spi_wait_for_miso_low();
    /* send register address byte */
    mcu_radio_spi_tx(accessType|addrByte);
    mcu_radio_spi_wait_done();
    /* Storing chip status */
    readValue = mcu_radio_spi_rx();
    trxReadWriteBurstSingle(accessType|addrByte,pData,len);
    mcu_radio_spi_end();
    /* return the status byte value */
    return(readValue);
}


/************************************************************************************************************************************/
/** @fcn        rfStatus_t trx16BitRegAccess(uint8 accessType, uint8 extAddr, uint8 regAddr, uint8 *pData, uint8 len)
 *  @brief      This function performs a read or write in the extended address space of CC112X.
 *  @details    x
 *
 *  @param       accessType - Specifies if this is a read or write and if it's a single or burst access. Bitmask made up of
 *                            RADIO_BURST_ACCESS/RADIO_SINGLE_ACCESS/RADIO_WRITE_ACCESS/RADIO_READ_ACCESS.
 *  @param       extAddr - Extended register space address = 0x2F.
 *  @param       regAddr - Register address in the extended address space.
 *  @param       *pData  - Pointer to data array for communication
 *  @param       len     - Length of bytes to be read/written from/to radio
 *
 *  @return      rfStatus_t
 */
/************************************************************************************************************************************/
rfStatus_t trx16BitRegAccess(uint8_t accessType, uint8_t extAddr, uint8_t regAddr, uint8_t *pData, uint8_t len) {

    uint8_t readValue;

    mcu_radio_spi_begin();
    mcu_radio_spi_wait_for_miso_low();
    /* send extended address byte with access type bits set */
    mcu_radio_spi_tx(accessType|extAddr);
    mcu_radio_spi_wait_done();
    /* Storing chip status */
    readValue = mcu_radio_spi_rx();
    mcu_radio_spi_tx(regAddr);
    mcu_radio_spi_wait_done();
    /* Communicate len number of bytes */
    trxReadWriteBurstSingle(accessType|extAddr,pData,len);
    mcu_radio_spi_end();

    /* return the status byte value */
    return(readValue);
}


/************************************************************************************************************************************/
/** @fcn        void trxReadWriteBurstSingle(uint8_t addr, uint8_t *pData, uint16_t len)
 *  @brief      When the address byte is sent to the SPI slave, the next byte communicated is the data to be written or read. The
 *              address byte that holds information about read/write -and single/burst-access is provided to this function
 *
 *              Depending on these two bits this function will write len bytes to the radio in burst mode or read len bytes from the
 *              radio in burst mode if the burst bit is set. If the burst bit is not set, only one data byte is communicated
 *
 *              NOTE: This function is used in the following way:
 *                  TRXEM_SPI_BEGIN();
 *                  while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);
 *                  ...[Depending on type of register access]
 *                  trxReadWriteBurstSingle(uint8 addr,uint8 *pData,uint16 len);
 *                  TRXEM_SPI_END();
 */
/************************************************************************************************************************************/
void trxReadWriteBurstSingle(uint8_t addr, uint8_t *pData, uint16_t len) {

    uint16_t i;

    /* Communicate len number of bytes: if RX - the procedure sends 0x00 to push bytes from slave*/
    if(addr&RADIO_READ_ACCESS) {

        if(addr&RADIO_BURST_ACCESS) {

            for(i = 0; i < len; i++) {
                mcu_radio_spi_tx(0);            /* Possible to combining read and write as one access type */
                mcu_radio_spi_wait_done();
                *pData = mcu_radio_spi_rx();     /* Store pData from last pData RX */
                pData++;
            }
        }
        else {
            mcu_radio_spi_tx(0);
            mcu_radio_spi_wait_done();
            *pData = mcu_radio_spi_rx();
        }
    }
    else {
        if(addr&RADIO_BURST_ACCESS) {
            /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
            for (i = 0; i < len; i++) {
                mcu_radio_spi_tx(*pData);
                mcu_radio_spi_wait_done();
                pData++;
            }
        }
        else {
            mcu_radio_spi_tx(*pData);
            mcu_radio_spi_wait_done();
        }
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        rfStatus_fields cc12xx_getRFStatusFields(uint8_t rfStatus_u8)
 *  @brief      Get the individual fields from the chip status byte
 *
 *  @param      [in]    (uint8_t) rfStatus_u8 - Chip Status Byte returned in response by cc12xx radio
 *
 *  @param      [out]   (rfStatus_fields)  field defs of status byte
 */
/************************************************************************************************************************************/
rfStatus_fields cc12xx_getRFStatusFields(uint8_t rfStatus_u8) {

    rfStatus_fields fields;

    fields.chip_rdy = (rfStatus_u8 & 0x80) >> 7;

    fields.state    = (chip_state) ((rfStatus_u8 & 0x70) >> 4);

    return fields;
}

