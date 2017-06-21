/************************************************************************************************************************************/
/** @file       cc1200.c
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
 *          do something better than the hard spin if id not matching (id_matches)
 *
 *  @section    Legal Disclaimer
 *          All contents of this source file and/or any other Misc. Product related source files are the explicit property of
 *          Misc. Company. Do not distribute. Do not copy.
 */
/************************************************************************************************************************************/
#include "cc1200.h"

/**
 * @note    applies 1ms reset pulse to EMK
 */
void cc1200_init(void) {

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
    trxSpiCmdStrobe(CC120X_SRES);

    //Verify ID
    bool valid_id = cc1200_verifyPartNumber();

    if(!valid_id) {
        for(;;);                                                           /* not the CC1200, spin                                  */
    }


    //******************************************************************************************************************************//
    // INIT RADIO CONFIG                                                                                                            //
    //******************************************************************************************************************************//
    cc1200_configure();                                                     /* configure the radio for use                          */


    //******************************************************************************************************************************//
    // CALIBRATE                                                                                                                    //
    //******************************************************************************************************************************//
    trxSpiCmdStrobe(CC120X_SCAL);

    // Wait for calibration to be done (radio back in IDLE state)
    do {
      cc120xSpiReadReg(CC120X_MARCSTATE, &marcState, 1);
    } while (marcState != 0x41);

    // Put radio in powerdown to save power
    trxSpiCmdStrobe(CC120X_SPWD);

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_spi_init(void)
 *  @brief      initialize the CC1200's SPI interface
 *  @details    x
 *
 * @src     direct copy trx_rf_spi.c:trxRfSpiInterfaceInit(0x10)
 *
 *  @param      [in]    (uint8) clockDivider - SMCLK/clockDivider gives SCLK frequency (0x10) <- <temp> 0x10
 *
 */
/************************************************************************************************************************************/
void cc1200_spi_init(void) {

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

    TRXEM_SPI_BEGIN();

    while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);

    TRXEM_SPI_TX(cmd);

    TRXEM_SPI_WAIT_DONE();

    rc = TRXEM_SPI_RX();

    TRXEM_SPI_END();

    return(rc);
}


/******************************************************************************
 * @fn          cc120xSpiReadReg
 *
 * @brief       Read value(s) from config/status/extended radio register(s).
 *              If len  = 1: Reads a single register
 *              if len != 1: Reads len register values in burst mode
 *
 * input parameters
 *
 * @param       addr   - address of first register to read
 * @param       *pData - pointer to data array where read bytes are saved
 * @param       len   - number of bytes to read
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc120xSpiReadReg(uint16_t addr, uint8_t *pData, uint8_t len) {

  uint8_t tempExt  = (uint8_t)(addr>>8);
  uint8_t tempAddr = (uint8_t)(addr & 0x00FF);
  uint8_t rc;


  /* Checking if this is a FIFO access -> returns chip not ready  */
  if((CC120X_SINGLE_TXFIFO<=tempAddr)&&(tempExt==0)) return STATUS_CHIP_RDYn_BM;

  /* Decide what register space is accessed */
  if(!tempExt) {
      rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempAddr,pData,len);
  }
  else if (tempExt == 0x2F) {
      rc = trx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),tempExt,tempAddr,pData,len);
  }
  return (rc);
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
    TRXEM_SPI_BEGIN();
    while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);
    /* send register address byte */
    TRXEM_SPI_TX(accessType|addrByte);
    TRXEM_SPI_WAIT_DONE();
    /* Storing chip status */
    readValue = TRXEM_SPI_RX();
    trxReadWriteBurstSingle(accessType|addrByte,pData,len);
    TRXEM_SPI_END();
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

    TRXEM_SPI_BEGIN();
    while(TRXEM_PORT_IN & TRXEM_SPI_MISO_PIN);
    /* send extended address byte with access type bits set */
    TRXEM_SPI_TX(accessType|extAddr);
    TRXEM_SPI_WAIT_DONE();
    /* Storing chip status */
    readValue = TRXEM_SPI_RX();
    TRXEM_SPI_TX(regAddr);
    TRXEM_SPI_WAIT_DONE();
    /* Communicate len number of bytes */
    trxReadWriteBurstSingle(accessType|extAddr,pData,len);
    TRXEM_SPI_END();

    /* return the status byte value */
    return(readValue);
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
        rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempAddr,pData,len);
    }
    else if (tempExt == 0x2F) {
        rc = trx16BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),tempExt,tempAddr,pData,len);
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
          TRXEM_SPI_TX(0);            /* Possible to combining read and write as one access type */
          TRXEM_SPI_WAIT_DONE();
          *pData = TRXEM_SPI_RX();     /* Store pData from last pData RX */
          pData++;
      }
    }
    else {
      TRXEM_SPI_TX(0);
      TRXEM_SPI_WAIT_DONE();
      *pData = TRXEM_SPI_RX();
    }
  }
  else {
    if(addr&RADIO_BURST_ACCESS) {
      /* Communicate len number of bytes: if TX - the procedure doesn't overwrite pData */
      for (i = 0; i < len; i++) {
        TRXEM_SPI_TX(*pData);
        TRXEM_SPI_WAIT_DONE();
        pData++;
      }
    }
    else {
      TRXEM_SPI_TX(*pData);
      TRXEM_SPI_WAIT_DONE();
    }
  }

  return;
}


/************************************************************************************************************************************/
/** @fcn        uint8_t cc1200_queryTxFifo(void)
 *  @brief      query the TX FIFO for #elements open for insertion
 *
 *  @pre        TX FIFO is initialized
 *
 *  @return     (uint32_t) open count
 */
/************************************************************************************************************************************/
uint8_t cc1200_queryTxFifo(void) {

    uint8_t fill_ct, open_ct;

    cc120xSpiReadReg(CC120X_NUM_TXBYTES, &fill_ct, 1);

    if(fill_ct < 128) {
        open_ct = 127 - fill_ct;
    } else {
        open_ct = 0;
    }

    return open_ct;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_configure(void)
 *  @brief      configure the radio for use
 *
 *  @pre        radio was reset
 *  @post       radio is ready for operation
 */
/************************************************************************************************************************************/
void cc1200_configure(void) {

    uint16_t i;

    for(i=0; i<NUM_PREFERRED_SETTINGS_CC1200; i++) {

        uint8_t data = preferredSettings[i].data;

        uint16_t addr = preferredSettings[i].addr;

        cc1200_reg_write(addr, data);
    }

    return;
}


/************************************************************************************************************************************/
/** @fcn        void cc1200_reg_write(uint16_t addr, uint8_t data)
 *  @brief      apply register values to configure the radio for use
 *
 *  @param      [in]    (uint16_t) addr - address
 *  @param      [in]    (uint8_t) data  - data to write
 *
 */
/************************************************************************************************************************************/
void cc1200_reg_write(uint16_t addr, uint8_t data) {

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
/** @fcn        void cc1200_reg_read(uint16_t addr, uint8_t *dataPtr)
 *  @brief      clean wrapper to read a single register value
 *
 *  @param      [in]    (uint16_t)  addr     - address
 *  @param      [in]    (uint8_t *) dataPtr  - where to store value
 *
 */
/************************************************************************************************************************************/
void cc1200_reg_read(uint16_t addr, uint8_t *dataPtr) {

    cc120xSpiReadReg(addr, dataPtr, 1);

    return;
}


/************************************************************************************************************************************/
/** @fcn        bool cc1200_verifyPartNumber(void)
 *  @brief      is the register value for [PARTNUMBER] match the CC1200?
 *
 *  @return     (bool) if Part Number is valid for CC1200
 */
/************************************************************************************************************************************/
bool cc1200_verifyPartNumber(void) {

    uint16_t i;

    uint8_t part_number;

    //small reset delay, cc12xx is non-deterministic on Reg-read values immediately after reset
    for(i=0; i<1000; i++) {
        asm(" NOP");
    }

    //Check Part Number
    cc120xSpiReadReg(CC120X_PARTNUMBER, &part_number, 1);

    return (part_number == CHIP_PARTNUMBER_CC1200);
}
