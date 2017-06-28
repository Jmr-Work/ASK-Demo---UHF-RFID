#include "cc2541_demo.h"

//#define   DEMO_OPTION_ONE     (1)                                         // simple Tx
#define   DEMO_OPTION_TWO     (1)                                         //  part number verification (manual call)
//#define     DEMO_OPTION_THREE     (1)                                       //  part number verification (api call)


#if defined(DEMO_OPTION_TWO) || defined(DEMO_OPTION_THREE)
    volatile uint8_t rx_val = 0x00;
#endif


/************************************************************************************************************************************/
/** @fcn        void cc2541_demo(void)
 *  @brief      x
 *  @details    x
 */
/************************************************************************************************************************************/
void cc2541_demo(void) {
  
    uint16_t i = 0x00;
        
    asm(" NOP");                                                            /* placeholder for dbg breakpoint                       */
    
    for(;;) {
      
#ifdef DEMO_OPTION_ONE      
        mcu_radio_spi_tx(0x55);
        
        //Small Delay
        for(i=0; i<50; i++) {
            asm(" NOP");
        }
#endif  
#ifdef DEMO_OPTION_TWO

        //CS LOW
        P1 &= ~BIT7;                                                        /* Misc. Dbg Pin                                        */
        RADIO_PORT &= ~RADIO_PIN_CS_N;                                      /* CS to begin comm                                     */
        
        while(RADIO_PORT & RADIO_PIN_MISO);
        
        U0DBUF = (RADIO_BURST_ACCESS|RADIO_READ_ACCESS)|0x2F;
        
        // Check if byte is transmitted
        while(!(U0CSR & U0CSR_TX_BYTE));

        // Clear transmit byte status
        U0CSR &= ~U0CSR_TX_BYTE;
        
        U0DBUF = 0x8F;
        
        // Check if byte is transmitted
        while(!(U0CSR & U0CSR_TX_BYTE));

        // Clear transmit byte status
        U0CSR &= ~U0CSR_TX_BYTE;

        //Grab PartNumber
        U0DBUF = 0x00;
            
        // Check if byte is transmitted
        while(!(U0CSR & U0CSR_TX_BYTE));

        // Clear transmit byte status
        U0CSR &= ~U0CSR_TX_BYTE;

        //Get Val
        rx_val = U0DBUF;
        
        //CS HIGH
        RADIO_PORT |= RADIO_PIN_CS_N;
        P1 |= BIT7;    
        
        
        //Small Delay
        for(i=0; i<50000; i++) {
            asm(" NOP");                                                    /* set to 20 kHz                                        */
        }
#endif
#ifdef DEMO_OPTION_THREE
        cc12xxSpiReadReg(CC120X_PARTNUMBER, (uint8_t *)&rx_val, 1);
        
        //Small Delay
        for(i=0; i<50000; i++) {
            asm(" NOP");                                                    /* set to 20 kHz                                        */
        }
#endif        
    }
}

