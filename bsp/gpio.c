#include "gpio.h"


/************************************************************************************************************************************/
/** @fcn        void gpio_init(void)
 *  @brief      init gpio on boot
 *  @details    x
 *
 *  @section    TrxEB r1.7 Config (ref - schem)
 *      RF1.10 - GPIO0  [P1.7]
 *      RF1.12 - GPIO2  [P1.3]
 *      RF1.14 - CSN    [P3.0 - RF_SPI0_CS_N]
 *      RF1.16 - SCLK   [P3.3 - RF_SPI0_SCLK]
 *      RF1.18 - MOSI   [P3.1 - RF_SPI0_MOSI]
 *      RF1.20 - MISO   [P3.2 - RF_SPI0_MISO]
 *      RF2.15 - RESET  [P8.0 - RF_RESET_N]
 *      RF2.18 - GPIO3  [P1.2]
 *
 *      RF2.2  - GND
 *      RF2.7  - VCC (3.3V)
 *      RF2.9  - VCC (3.3V)
 *      RF1.1  - GND
 *      RF1.19 - GND
 *
 *
 *  @section    Measured Clock Values on GPIO Outputs
 *      P11.0 - 32.73 kHz
 *      P11.1 - 16.13 MHz
 *      P11.2 - 16.13 MHz
 */
/************************************************************************************************************************************/
void gpio_init(void) {

#ifdef TARGET_IS_MSP430F5438A
    msp430f5438a_gpio_init();
#endif

    return;
}

