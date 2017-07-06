/************************************************************************************************************************************/
/** @file       iocc2541_jmr.h
 *  @brief      #def inclusions for review within Eclipse, not for compilation or use
 *  @details    direct value derivations from IAR ioc2541.h
 *
 *  @source     iocc2541.h (IAR)
 *
 *  @info       Header file with definitions for the Texas Instruments CC2541 low-power System-on-Chip:
 *                  an 8051-based MCU with 2.4 GHz Bluetooth low energy RF transceiver, and up to 256 kB FLASH
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
#ifndef BSP_TARGETS_SUPPORT_IOCC2541_JMR_H_
#define BSP_TARGETS_SUPPORT_IOCC2541_JMR_H_

#ifdef USING_ECLIPSE

/* IAR assembler uses some predefined registers. The following prevents name collisions. */
#define SP   SPx
#define ACC  ACCx
#define B    Bx
#define PSW  PSWx
#define CY   CYx
#define AC   ACx
#define F0   F0x
#define RS1  RS1x
#define RS0  RS0x
#define OV   OVx
#define P    Px

#define  RFERR_VECTOR   VECT(  0, 0x03 )   /*  RF core error situation                     */
#define  ADC_VECTOR     VECT(  1, 0x0B )   /*  ADC end of conversion                       */
#define  URX0_VECTOR    VECT(  2, 0x13 )   /*  USART 0 RX complete                         */
#define  URX1_VECTOR    VECT(  3, 0x1B )   /*  USART 1 RX complete                         */
#define  ENC_VECTOR     VECT(  4, 0x23 )   /*  AES encryption/decryption complete          */
#define  ST_VECTOR      VECT(  5, 0x2B )   /*  Sleep Timer Compare                         */
#define  P2INT_VECTOR   VECT(  6, 0x33 )   /*  Port 2 Inputs and I2C                       */
#define  UTX0_VECTOR    VECT(  7, 0x3B )   /*  USART0 TX Complete                          */
#define  DMA_VECTOR     VECT(  8, 0x43 )   /*  DMA Transfer Complete                       */
#define  T1_VECTOR      VECT(  9, 0x4B )   /*  Timer 1 (16-bit) Capture/Compare/Overflow   */
#define  T2_VECTOR      VECT( 10, 0x53 )   /*  Timer 2                                     */
#define  T3_VECTOR      VECT( 11, 0x5B )   /*  Timer 3 (8-bit) Capture/Compare/Overflow    */
#define  T4_VECTOR      VECT( 12, 0x63 )   /*  Timer 4 (8-bit) Capture/Compare/Overflow    */
#define  P0INT_VECTOR   VECT( 13, 0x6B )   /*  Port 0 Inputs                               */
#define  UTX1_VECTOR    VECT( 14, 0x73 )   /*  USART1 TX Complete                          */
#define  P1INT_VECTOR   VECT( 15, 0x7B )   /*  Port 1 Inputs                               */
#define  RF_VECTOR      VECT( 16, 0x83 )   /*  RF General Interrupts                       */
#define  WDT_VECTOR     VECT( 17, 0x8B )   /*  Watchdog Overflow in Timer Mode             */


//Interrupt Alias
#define  I2C_VECTOR     P2INT_VECTOR       /*  I2C Interrupt vector, alias for P2INT_VECTOR */

//SFRs
/** @brief  SFRs with an address ending with 0/8 are bit accessible. They are defined with SFRBIT() that sets the name of each bit
 */

//Port 0
#define  P0          0x80
#define  P0_7        0x80
#define  P0_6        0x80
#define  P0_5        0x80
#define  P0_4        0x80
#define  P0_3        0x80
#define  P0_2        0x80
#define  P0_1        0x80
#define  P0_0        0x80
#define  SP          0x81                                                   /*  Stack Pointer                                       */
#define  DPL0        0x82                                                   /*  Data Pointer 0 Low Byte                             */
#define  DPH0        0x83                                                   /*  Data Pointer 0 High Byte                            */
#define  DPL1        0x84                                                   /*  Data Pointer 1 Low Byte                             */
#define  DPH1        0x85                                                   /*  Data Pointer 1 High Byte                            */
#define  U0CSR       0x86                                                   /*  USART 0 Control and Status                          */
#define  PCON        0x87                                                   /*  Power Mode Control                                  */

//Interrupt Flags
#define  TCON        0x88
#define  URX1IF      0x88
#define  ADCIF       0x88
#define  URX0IF      0x88
#define  RFERRIF     0x88
#define  P0IFG       0x89                                                   /*  Port 0 Interrupt Status Flag                        */
#define  P1IFG       0x8A                                                   /*  Port 1 Interrupt Status Flag                        */
#define  P2IFG       0x8B                                                   /*  Port 2 Interrupt Status Flag                        */
#define  PICTL       0x8C                                                   /*  Port Interrupt Control                              */
#define  P1IEN       0x8D                                                   /*  Port 1 Interrupt Mask                               */
#define  P0INP       0x8F                                                   /*  Port 0 Input Mode                                   */

//Port 1
#define  P1          0x90
#define  P1_7        0x90
#define  P1_6        0x90
#define  P1_5        0x90
#define  P1_4        0x90
#define  P1_3        0x90
#define  P1_2        0x90
#define  P1_1        0x90
#define  P1_0        0x90
#define  RFIRQF1     0x91                                                   /*  RF Interrupt Flags MSB                              */
#define  DPS         0x92                                                   /*  Data Pointer Select                                 */
#define  MPAGE       0x93                                                   /*  Memory Page Select                                  */
#define  T2CTRL      0x94                                                   /*  Timer2 Control Register                             */
#define  ST0         0x95                                                   /*  Sleep Timer 0                                       */
#define  ST1         0x96                                                   /*  Sleep Timer 1                                       */
#define  ST2         0x97                                                   /*  Sleep Timer 2                                       */

//Interrupt Flags 2
#define  S0CON       0x98
#define  _S0CON7     0x98
#define  _S0CON6     0x98
#define  _S0CON5     0x98
#define  _S0CON4     0x98
#define  _S0CON3     0x98
#define  _S0CON2     0x98
#define  ENCIF_1     0x98
#define  ENCIF_0     0x98
#define  _SFR99      0x99                                                   /*  reserved                                            */
#define  IEN2        0x9A                                                   /*  Interrupt Enable 2                                  */
#define  S1CON       0x9B                                                   /*  Interrupt Flags 3                                   */
#define  T2CSPCFG    0x9C                                                   /*  Timer2 CSP Interface Configuration (legacy name)    */
#define  T2EVTCFG    0x9C                                                   /*  Timer2 Event Output Configuration                   */
#define  SLEEPSTA    0x9D                                                   /*  Sleep Status                                        */
#define  CLKCONSTA   0x9E                                                   /*  Clock Control Status                                */
#define  FMAP        0x9F                                                   /*  Flash Bank Map                                      */

//Port 2
#define  P2          0xA0
#define  _P2_7       0xA0
#define  _P2_6       0xA0
#define  _P2_5       0xA0
#define  P2_4        0xA0
#define  P2_3        0xA0
#define  P2_2        0xA0
#define  P2_1        0xA0
#define  P2_0        0xA0
#define  T2IRQF      0xA1                                                   /* Timer2 Interrupt Flags                               */
#define  T2M0        0xA2                                                   /* Timer2 Multiplexed Register 0                        */
#define  T2M1        0xA3                                                   /* Timer2 Multiplexed Register 1                        */
#define  T2MOVF0     0xA4                                                   /* Timer2 Multiplexed Overflow Register 0               */
#define  T2MOVF1     0xA5                                                   /* Timer2 Multiplexed Overflow Register 1               */
#define  T2MOVF2     0xA6                                                   /* Timer2 Multiplexed Overflow Register 2               */
#define  T2IRQM      0xA7                                                   /* Timer2 Interrupt Masks                               */

//Interrupt Enable 0
#define  IEN0        0xA8
#define  EA          0xA8
#define  _IEN06      0xA8
#define  STIE        0xA8
#define  ENCIE       0xA8
#define  URX1IE      0xA8
#define  URX0IE      0xA8
#define  ADCIE       0xA8
#define  RFERRIE     0xA8
#define  IP0         0xA9                                                   /*  Interrupt Priority 0                                */
#define  _SFRAA      0xAA                                                   /*  not used                                            */
#define  P0IEN       0xAB                                                   /*  Port 0 Interrupt Mask                               */
#define  P2IEN       0xAC                                                   /*  Port 2 Interrupt Mask                               */
#define  STLOAD      0xAD                                                   /*  Sleep Timer Load Status                             */
#define  PMUX        0xAE                                                   /*  Power Down Signal MUX                               */
#define  T1STAT      0xAF                                                   /*  Timer 1 Status                                      */

#define  _SFRB0      0xB0                                                   /*  not used                                            */
#define  ENCDI       0xB1                                                   /*  Encryption/Decryption Input Data                    */
#define  ENCDO       0xB2                                                   /*  Encryption/Decryption Output Data                   */
#define  ENCCS       0xB3                                                   /*  Encryption/Decryption Control and Status            */
#define  ADCCON1     0xB4                                                   /*  ADC Control 1                                       */
#define  ADCCON2     0xB5                                                   /*  ADC Control 2                                       */
#define  ADCCON3     0xB6                                                   /*  ADC Control 3                                       */
#define  _SFRB7      0xB7                                                   /*  reserved                                            */

//Interrupt Enable 1
#define  IEN1        0xB8
#define  _IEN17      0xB8
#define  _IEN16      0xB8
#define  P0IE        0xB8
#define  T4IE        0xB8
#define  T3IE        0xB8
#define  T2IE        0xB8
#define  T1IE        0xB8
#define  DMAIE       0xB8
#define  IP1         0xB9                                                   /*  Interrupt Priority 1                                */
#define  ADCL        0xBA                                                   /*  ADC Data Low                                        */
#define  ADCH        0xBB                                                   /*  ADC Data High                                       */
#define  RNDL        0xBC                                                   /*  Random Number Generator Low Byte                    */
#define  RNDH        0xBD                                                   /*  Random Number Generator High Byte                   */
#define  SLEEPCMD    0xBE                                                   /*  Sleep Mode Control Command                          */
#define  RFERRF      0xBF                                                   /*  RF Error Interrupt Flags                            */

//Interrupt Flags 4
#define  IRCON       0xC0
#define  STIF        0xC0
#define  _IRCON6     0xC0
#define  P0IF        0xC0
#define  T4IF        0xC0
#define  T3IF        0xC0
#define  T2IF        0xC0
#define  T1IF        0xC0
#define  DMAIF       0xC0
#define  U0DBUF      0xC1                                                   /*  USART 0 Receive/Transmit Data Buffer                */
#define  U0BAUD      0xC2                                                   /*  USART 0 Baud Rate Control                           */
#define  T2MSEL      0xC3                                                   /*  Timer2 Multiplex Select                             */
#define  U0UCR       0xC4                                                   /*  USART 0 UART Control                                */
#define  U0GCR       0xC5                                                   /*  USART 0 Generic Control                             */
#define  CLKCONCMD   0xC6                                                   /*  Clock Control Command                               */
#define  MEMCTR      0xC7                                                   /*  Memory System Control                               */

#define  _SFRC8      0xC8                                                   /*  not used                                            */
#define  WDCTL       0xC9                                                   /*  Watchdog Timer Control                              */
#define  T3CNT       0xCA                                                   /*  Timer 3 Counter                                     */
#define  T3CTL       0xCB                                                   /*  Timer 3 Control                                     */
#define  T3CCTL0     0xCC                                                   /*  Timer 3 Channel 0 Capture/Compare Control           */
#define  T3CC0       0xCD                                                   /*  Timer 3 Channel 0 Capture/Compare Value             */
#define  T3CCTL1     0xCE                                                   /*  Timer 3 Channel 1 Capture/Compare Control           */
#define  T3CC1       0xCF                                                   /*  Timer 3 Channel 1 Capture/Compare Value             */

//Program Status Word
#define  PSW         0xD0
#define  CY          0xD0
#define  AC          0xD0
#define  F0          0xD0
#define  RS1         0xD0
#define  RS0         0xD0
#define  OV          0xD0
#define  F1          0xD0
#define  P           0xD0
#define  DMAIRQ      0xD1                                                   /*  DMA Interrupt Flag                                  */
#define  DMA1CFGL    0xD2                                                   /*  DMA Channel 1-4 Configuration Address Low Byte      */
#define  DMA1CFGH    0xD3                                                   /*  DMA Channel 1-4 Configuration Address High Byte     */
#define  DMA0CFGL    0xD4                                                   /*  DMA Channel 0 Configuration Address Low Byte        */
#define  DMA0CFGH    0xD5                                                   /*  DMA Channel 0 Configuration Address High Byte       */
#define  DMAARM      0xD6                                                   /*  DMA Channel Arm                                     */
#define  DMAREQ      0xD7                                                   /*  DMA Channel Start Request and Status                */

//Timers 1/3/4 Interrupt Mask/Flag
#define  TIMIF       0xD8
#define  _TIMIF7     0xD8
#define  T1OVFIM     0xD8
#define  T4CH1IF     0xD8
#define  T4CH0IF     0xD8
#define  T4OVFIF     0xD8
#define  T3CH1IF     0xD8
#define  T3CH0IF     0xD8
#define  T3OVFIF     0xD8
#define  RFD         0xD9                                                   /*  RF Data                                             */
#define  T1CC0L      0xDA                                                   /*  Timer 1 Channel 0 Capture/Compare Value Low Byte    */
#define  T1CC0H      0xDB                                                   /*  Timer 1 Channel 0 Capture/Compare Value High Byte   */
#define  T1CC1L      0xDC                                                   /*  Timer 1 Channel 1 Capture/Compare Value Low Byte    */
#define  T1CC1H      0xDD                                                   /*  Timer 1 Channel 1 Capture/Compare Value High Byte   */
#define  T1CC2L      0xDE                                                   /*  Timer 1 Channel 2 Capture/Compare Value Low Byte    */
#define  T1CC2H      0xDF                                                   /*  Timer 1 Channel 2 Capture/Compare Value High Byte   */

#define  ACC         0xE0                                                   /*  Accumulator                                         */
#define  RFST        0xE1                                                   /*  RF Command Strobe                                   */
#define  T1CNTL      0xE2                                                   /*  Timer 1 Counter Low                                 */
#define  T1CNTH      0xE3                                                   /*  Timer 1 Counter High                                */
#define  T1CTL       0xE4                                                   /*  Timer 1 Control And Status                          */
#define  T1CCTL0     0xE5                                                   /*  Timer 1 Channel 0 Capture/Compare Control           */
#define  T1CCTL1     0xE6                                                   /*  Timer 1 Channel 1 Capture/Compare Control           */
#define  T1CCTL2     0xE7                                                   /*  Timer 1 Channel 2 Capture/Compare Control           */

//Interrupt Flags 5
#define  IRCON2      0xE8
#define  _IRCON27    0xE8
#define  _IRCON26    0xE8
#define  _IRCON25    0xE8
#define  WDTIF       0xE8
#define  P1IF        0xE8
#define  UTX1IF      0xE8
#define  UTX0IF      0xE8
#define  P2IF        0xE8
#define  RFIRQF0     0xE9                                                   /*  RF Interrupt Flags LSB                              */
#define  T4CNT       0xEA                                                   /*  Timer 4 Counter                                     */
#define  T4CTL       0xEB                                                   /*  Timer 4 Control                                     */
#define  T4CCTL0     0xEC                                                   /*  Timer 4 Channel 0 Capture/Compare Control           */
#define  T4CC0       0xED                                                   /*  Timer 4 Channel 0 Capture/Compare Value             */
#define  T4CCTL1     0xEE                                                   /*  Timer 4 Channel 1 Capture/Compare Control           */
#define  T4CC1       0xEF                                                   /*  Timer 4 Channel 1 Capture/Compare Value             */

#define  B           0xF0                                                   /*  B Register                                          */
#define  PERCFG      0xF1                                                   /*  Peripheral I/O Control                              */
#define  ADCCFG      0xF2                                                   /*  ADC Input Configuration (legacy name)               */
#define  APCFG       0xF2                                                   /*  Analog Peripheral I/O Configuration                 */
#define  P0SEL       0xF3                                                   /*  Port 0 Function Select                              */
#define  P1SEL       0xF4                                                   /*  Port 1 Function Select                              */
#define  P2SEL       0xF5                                                   /*  Port 2 Function Select                              */
#define  P1INP       0xF6                                                   /*  Port 1 Input Mode                                   */
#define  P2INP       0xF7                                                   /*  Port 2 Input Mode                                   */

//USART 1 Control and Status
#define  U1CSR       0xF8
#define  U1MODE      0xF8
#define  U1RE        0xF8
#define  U1SLAVE     0xF8
#define  U1FE        0xF8
#define  U1ERR       0xF8
#define  U1RX_BYTE   0xF8
#define  U1TX_BYTE   0xF8
#define  U1ACTIVE    0xF8
#define  U1DBUF      0xF9                                                   /*  USART 1 Receive/Transmit Data Buffer                */
#define  U1BAUD      0xFA                                                   /*  USART 1 Baud Rate Control                           */
#define  U1UCR       0xFB                                                   /*  USART 1 UART Control                                */
#define  U1GCR       0xFC                                                   /*  USART 1 Generic Control                             */
#define  P0DIR       0xFD                                                   /*  Port 0 Direction                                    */
#define  P1DIR       0xFE                                                   /*  Port 1 Direction                                    */
#define  P2DIR       0xFF                                                   /*  Port 2 Direction                                    */



//Xdata Radio Registers
/* RF core ram */
#define RFCORE_RAM_SZ   1024

/* RF core ram register/general memory page */
#define RFCORE_RAM_PAGE_SZ 128

/* FIFO direct access */
#define RXFIFO          0x6080
#define RXFIFO_SZ       128
#define TXFIFO          0x6100
#define TXFIFO_SZ       128

/* Radio Control Registers */
#define FRMCTRL0       (0x6180)
#define RFIRQM0        (0x6181)
#define RFIRQM1        (0x6182)
#define RFERRM         (0x6183)
#define FREQCTRL       (0x6184)
#define FREQTUNE       (0x6185)
#define TXPOWER        (0x6186)
#define TXCTRL         (0x6187)
#define LLESTAT        (0x6188)
#define _XREG6189      (0x6189)
#define SEMAPHORE0     (0x618A)
#define SEMAPHORE1     (0x618B)
#define SEMAPHORE2     (0x618C)
#define RFSTAT         (0x618D)
#define RSSI           (0x618E)
#define RFPSRND        (0x618F)
#define MDMCTRL0       (0x6190)
#define MDMCTRL1       (0x6191)
#define MDMCTRL2       (0x6192)
#define MDMCTRL3       (0x6193)
#define SW_CONF        (0x6194)
#define SW0            (0x6195)
#define SW1            (0x6196)
#define SW2            (0x6197)
#define SW3            (0x6198)
#define SW4            (0x61F8)
#define SW5            (0x61F9)
#define SW6            (0x61FA)
#define SW7            (0x61FB)
#define FREQEST        (0x6199)
#define RXCTRL         (0x619A)
#define FSCTRL         (0x619B)
#define _XREG619C      (0x619C)
#define _XREG619D      (0x619D)
#define _XREG619E      (0x619E)
#define _XREG619F      (0x619F)
#define LNAGAIN        (0x61A0)
#define AAFGAIN        (0x61A1)
#define ADCTEST0       (0x61A2)

#define MDMTEST0       (0x61A5)
#define MDMTEST1       (0x61A6)
#define _XREG61A7      (0x61A7)
#define _XREG61A8      (0x61A8)
#define ATEST          (0x61A9)
#define RFC_OBS_CTRL0  (0x61AE)
#define RFC_OBS_CTRL1  (0x61AF)
#define RFC_OBS_CTRL2  (0x61B0)
#define LLECTRL        (0x61B1)
#define TXFILTCFG      (0x61BC)
#define RFRND          (0x61BF)
#define RFRAMCFG       (0x61C0)
#define RFFDMA0        (0x61C3)
#define RFFDMA1        (0x61C4)
#define RFFSTATUS      (0x61C5)
#define RFFCFG         (0x61C6)
#define RFRXFLEN       (0x61C8)
#define RFRXFTHRS      (0x61C9)
#define RFRXFWR        (0x61CA)
#define RFRXFRD        (0x61CB)
#define RFRXFWP        (0x61CC)
#define RFRXFRP        (0x61CD)
#define RFRXFSWP       (0x61CE)
#define RFRXFSRP       (0x61CF)
#define RFTXFLEN       (0x61D0)
#define RFTXFTHRS      (0x61D1)
#define RFTXFWR        (0x61D2)
#define RFTXFRD        (0x61D3)
#define RFTXFWP        (0x61D4)
#define RFTXFRP        (0x61D5)
#define RFTXFSWP       (0x61D6)
#define RFTXFSRP       (0x61D7)
#define BSP_P0         (0x61E0)
#define BSP_P1         (0x61E1)
#define BSP_P2         (0x61E2)
#define BSP_P3         (0x61E3)
#define BSP_D0         (0x61E4)
#define BSP_D1         (0x61E5)
#define BSP_D2         (0x61E6)
#define BSP_D3         (0x61E7)
#define BSP_W          (0x61E8)
#define BSP_MODE       (0x61E9)
#define BSP_DATA       (0x61EA)
#define DC_I_L         (0x61FC)
#define DC_I_H         (0x61FD)
#define DC_Q_L         (0x61FE)
#define DC_Q_H         (0x61FF)


//Xdata Registers
/* Power-Management Registers */
#define SRCRC           (0x6262)

/* Observability Control */
#define OBSSEL0         (0x6243)
#define OBSSEL1         (0x6244)
#define OBSSEL2         (0x6245)
#define OBSSEL3         (0x6246)
#define OBSSEL4         (0x6247)
#define OBSSEL5         (0x6248)
#define TR0             (0x624B)

/* Chip Identification */
#define CHVER           (0x6249)
#define CHIPID          (0x624A)

/* Debug Interface DMA Write to Flash */
#define DBGDATA         (0x6260)

/* Flash Controller */
#define FCTL            (0x6270)
#define FADDRL          (0x6271)
#define FADDRH          (0x6272)
#define FWDATA          (0x6273)
#define FWT_HSOSC       (0x6274)
#define FWT_XOSC        (0x6275)

/* Chip Information */
#define CHIPINFO0       (0x6276)
#define CHIPINFO1       (0x6277)

/* IR Generation Control */
#define IRCTL           (0x6281)

/* Clock Loss Detector */
#define CLD             (0x6290)

/* Timer 1 Channels (only mapped as XREG) */
#define T1CCTL3         (0x62A3)
#define T1CCTL4         (0x62A4)
#define T1CC3L          (0x62AC)
#define T1CC3H          (0x62AD)
#define T1CC4L          (0x62AE)
#define T1CC4H          (0x62AF)
/* Definition which includes channels represented in SFR (additional XREG mapping of SFR) */
#define XX_T1CCTL0      (0x62A0)
#define XX_T1CCTL1      (0x62A1)
#define XX_T1CCTL2      (0x62A2)
#define XX_T1CCTL3      (0x62A3)
#define XX_T1CCTL4      (0x62A4)
#define XX_T1CC0L       (0x62A6)
#define XX_T1CC0H       (0x62A7)
#define XX_T1CC1L       (0x62A8)
#define XX_T1CC1H       (0x62A9)
#define XX_T1CC2L       (0x62AA)
#define XX_T1CC2H       (0x62AB)
#define XX_T1CC3L       (0x62AC)
#define XX_T1CC3H       (0x62AD)
#define XX_T1CC4L       (0x62AE)
#define XX_T1CC4H       (0x62AF)
/* Pointers for array access */
#define P_T1CCTL        P(0x62A0)
#define P_T1CC          P(0x62A6)

/* Sleep Timer Capture Control */
#define STCC            (0x62B0)
#define STCS            (0x62B1)
#define STCV0           (0x62B2)
#define STCV1           (0x62B3)
#define STCV2           (0x62B4)

/* Op.Amp. Control */
#define OPAMPMC         (0x61AD)
#define OPAMPC          (0x62C0)
#define OPAMPS          (0x62C1)

/* Analog Comparator Control */
#define CMPCTL          (0x62D0)

/* I2C */
#define I2CCFG          (0x6230)
#define I2CSTAT         (0x6231)
#define I2CDATA         (0x6232)
#define I2CADDR         (0x6233)
#define I2CWC           (0x6234)
#define I2CIO           (0x6235)

/* Other */
#define IVCTRL          (0x6265)

//Xdata Mapped SFRs
/**
 *   Most SFRs are also accessible through XDATA address space.  The register definitions for
 *   this type of access are listed below.  The register names are identical to the SFR names
 *   but with the prefix X_ to denote an XDATA register.
 *
 *   Some SFRs are not accessible through XDATA space.  For clarity, entries are included for these
 *   registers.  They have a prefix of _NA to denote "not available."
 *
 *   For register descriptions, refer to the actual SFR declarations elsewhere in this file
 */

#define X_P0        (0x7080)                                                /*  Port 0. NOTE! Read-only access from XREG.           */
#define _NA_SP      (0x7081)
#define _NA_DPL0    (0x7082)
#define _NA_DPH0    (0x7083)
#define _NA_DPL1    (0x7084)
#define _NA_DPH1    (0x7085)
#define X_U0CSR     (0x7086)                                                /*  USART 0 Control and Status                          */
#define _NA_PCON    (0x7087)

#define _NA_TCON    (0x7088)
#define X_P0IFG     (0x7089)                                                /*  Port 0 Interrupt Status Flag                        */
#define X_P1IFG     (0x708A)                                                /*  Port 1 Interrupt Status Flag                        */
#define X_P2IFG     (0x708B)                                                /*  Port 2 Interrupt Status Flag                        */
#define X_PICTL     (0x708C)                                                /*  Port Interrupt Control                              */
#define X_P1IEN     (0x708D)                                                /*  Port 1 Interrupt Mask                               */
#define _NA_SFR8E   (0x708E)
#define X_P0INP     (0x708F)                                                /*  Port 0 Input Mode                                   */

#define X_P1        (0x7090)                                                /*  Port 1. NOTE! Read-only access from XREG.           */
#define X_RFIRQF1   (0x7091)                                                /*  RF Interrupt Flags MSB                              */
#define _NA_DPS     (0x7092)
#define X_MPAGE     (0x7093)                                                /*  Memory Page Select                                  */
#define X_T2CTRL    (0x7094)                                                /*  Timer2 Control Register                             */
#define X_ST0       (0x7095)                                                /*  Sleep Timer 0                                       */
#define X_ST1       (0x7096)                                                /*  Sleep Timer 1                                       */
#define X_ST2       (0x7097)                                                /*  Sleep Timer 2                                       */

#define _NA_S0CON   (0x7098)
#define _NA_SFR99   (0x7099)
#define _NA_IEN2    (0x709A)
#define _NA_S1CON   (0x709B)
#define X_T2CSPCFG  (0x709C)                                                /*  Timer2 CSP Interface Configuration (legacy name)    */
#define X_T2EVTCFG  (0x709C)                                                /*  Timer2 Event Output Configuration                   */
#define X_SLEEPSTA  (0x709D)                                                /*  Sleep Status                                        */
#define X_CLKCONSTA (0x709E)                                                /*  Clock Control Status                                */
#define X_FMAP      (0x709F)                                                /*  Flash Bank Map                                      */

#define X_P2        (0x70A0)                                                /*  Port 2. NOTE! Read-only access from XREG.           */
#define X_T2IRQF    (0x70A1)                                                /*  Timer2 Interrupt Flags                              */
#define X_T2M0      (0x70A2)                                                /*  Timer2 Multiplexed Register 0                       */
#define X_T2M1      (0x70A3)                                                /*  Timer2 Multiplexed Register 1                       */
#define X_T2MOVF0   (0x70A4)                                                /*  Timer2 Multiplexed Overflow Register 0              */
#define X_T2MOVF1   (0x70A5)                                                /*  Timer2 Multiplexed Overflow Register 1              */
#define X_T2MOVF2   (0x70A6)                                                /*  Timer2 Multiplexed Overflow Register 2              */
#define X_T2IRQM    (0x70A7)                                                /*  Timer2 Interrupt Mask                               */

#define _NA_IEN0    (0x70A8)
#define _NA_IP0     (0x70A9)
#define _NA_SFRAA   (0x70AA)
#define X_P0IEN     (0x70AB)                                                /*                                                      */
#define X_P2IEN     (0x70AC)                                                /*                                                      */
#define X_STLOAD    (0x70AD)                                                /*  Sleep Timer Load Status                             */
#define X_PMUX      (0x70AE)                                                /*                                                      */
#define X_T1STAT    (0x70AF)                                                /*                                                      */

#define _NA_SFRB0   (0x70A8)
#define X_ENCDI     (0x70B1)                                                /*  Encryption Input Data                               */
#define X_ENCDO     (0x70B2)                                                /*  Encryption Output Data                              */
#define X_ENCCS     (0x70B3)                                                /*  Encryption Control and Status                       */
#define X_ADCCON1   (0x70B4)                                                /*  ADC Control 1                                       */
#define X_ADCCON2   (0x70B5)                                                /*  ADC Control 2                                       */
#define X_ADCCON3   (0x70B6)                                                /*  ADC Control 3                                       */
#define _NA_SFRB7   (0x70B7)

#define _NA_IEN1    (0x70B8)
#define _NA_IP1     (0x70B9)
#define X_ADCL      (0x70BA)                                                /*  ADC Data Low                                        */
#define X_ADCH      (0x70BB)                                                /*  ADC Data High                                       */
#define X_RNDL      (0x70BC)                                                /*  Random Register Low Byte                            */
#define X_RNDH      (0x70BD)                                                /*  Random Register High Byte                           */
#define X_SLEEPCMD  (0x70BE)                                                /*  Sleep Mode Command                                  */
#define X_RFERRF    (0x70BF)                                                /*  RF Error Interrupt Flags                            */

#define _NA_IRCON   (0x70C0)
#define X_U0DBUF    (0x70C1)                                                /*  USART 0 Receive/Transmit Data Buffer                */
#define X_U0BAUD    (0x70C2)                                                /*  USART 0 Baud Rate Control                           */
#define X_T2MSEL    (0x70C3)                                                /*  Timer2 Multiplex Select                             */
#define X_U0UCR     (0x70C4)                                                /*  USART 0 UART Control                                */
#define X_U0GCR     (0x70C5)                                                /*  USART 0 Generic Control                             */
#define X_CLKCONCMD (0x70C6)                                                /*  Clock Control Command                               */
#define X_MEMCTR    (0x70C7)                                                /*  Memory Arbiter Control                              */

#define _NA_SFRC8   (0x70C8)
#define X_WDCTL     (0x70C9)                                                /*  Watchdog Timer Control                              */
#define X_T3CNT     (0x70CA)                                                /*  Timer 3 Counter                                     */
#define X_T3CTL     (0x70CB)                                                /*  Timer 3 Control                                     */
#define X_T3CCTL0   (0x70CC)                                                /*  Timer 3 Channel 0 Capture/Compare Control           */
#define X_T3CC0     (0x70CD)                                                /*  Timer 3 Channel 0 Capture/Compare Value             */
#define X_T3CCTL1   (0x70CE)                                                /*  Timer 3 Channel 1 Capture/Compare Control           */
#define X_T3CC1     (0x70CF)                                                /*  Timer 3 Channel 1 Capture/Compare Value             */

#define _NA_PSW     (0x70D0)
#define X_DMAIRQ    (0x70D1)                                                /*  DMA Interrupt Flag                                  */
#define X_DMA1CFGL  (0x70D2)                                                /*  DMA Channel 1-4 Configuration Address Low Byte      */
#define X_DMA1CFGH  (0x70D3)                                                /*  DMA Channel 1-4 Configuration Address High Byte     */
#define X_DMA0CFGL  (0x70D4)                                                /*  DMA Channel 0 Configuration Address Low Byte        */
#define X_DMA0CFGH  (0x70D5)                                                /*  DMA Channel 0 Configuration Address High Byte       */
#define X_DMAARM    (0x70D6)                                                /*  DMA Channel Arm                                     */
#define X_DMAREQ    (0x70D7)                                                /*  DMA Channel Start Request and Status                */

#define X_TIMIF     (0x70D8)                                                /*  Timers 1/3/4 Interrupt Mask/Flag                    */
#define X_RFD       (0x70D9)                                                /*  RF Data                                             */
#define X_T1CC0L    (0x70DA)                                                /*  Timer 1 Channel 0 Capture/Compare Value Low Byte    */
#define X_T1CC0H    (0x70DB)                                                /*  Timer 1 Channel 0 Capture/Compare Value High Byte   */
#define X_T1CC1L    (0x70DC)                                                /*  Timer 1 Channel 1 Capture/Compare Value Low Byte    */
#define X_T1CC1H    (0x70DD)                                                /*  Timer 1 Channel 1 Capture/Compare Value High Byte   */
#define X_T1CC2L    (0x70DE)                                                /*  Timer 1 Channel 2 Capture/Compare Value Low Byte    */
#define X_T1CC2H    (0x70DF)                                                /*  Timer 1 Channel 2 Capture/Compare Value High Byte   */

#define _NA_ACC     (0x70E0)
#define X_RFST      (0x70E1)                                                /*  RF Command Strobe                                   */
#define X_T1CNTL    (0x70E2)                                                /*  Timer 1 Counter Low                                 */
#define X_T1CNTH    (0x70E3)                                                /*  Timer 1 Counter High                                */
#define X_T1CTL     (0x70E4)                                                /*  Timer 1 Control and Status                          */
#define X_T1CCTL0   (0x70E5)                                                /*  Timer 1 Channel 0 Capture/Compare Control           */
#define X_T1CCTL1   (0x70E6)                                                /*  Timer 1 Channel 1 Capture/Compare Control           */
#define X_T1CCTL2   (0x70E7)                                                /*  Timer 1 Channel 2 Capture/Compare Control           */

#define _NA_IRCON2  (0x70E8)
#define X_RFIRQF0   (0x70E9)                                                /*  RF Interrupt Flags MSB                              */
#define X_T4CNT     (0x70EA)                                                /*  Timer 4 Counter                                     */
#define X_T4CTL     (0x70EB)                                                /*  Timer 4 Control                                     */
#define X_T4CCTL0   (0x70EC)                                                /*  Timer 4 Channel 0 Capture/Compare Control           */
#define X_T4CC0     (0x70ED)                                                /*  Timer 4 Channel 0 Capture/Compare Value             */
#define X_T4CCTL1   (0x70EE)                                                /*  Timer 4 Channel 1 Capture/Compare Control           */
#define X_T4CC1     (0x70EF)                                                /*  Timer 4 Channel 1 Capture/Compare Value             */

#define _NA_B       (0x70F0)
#define X_PERCFG    (0x70F1)                                                /*  Peripheral Control                                  */
#define X_ADCCFG    (0x70F2)                                                /*  ADC Input Configuration (legacy name)               */
#define X_APCFG     (0x70F2)                                                /*  Analog Peripheral I/O Configuration                 */
#define X_P0SEL     (0x70F3)                                                /*  Port 0 Function Select                              */
#define X_P1SEL     (0x70F4)                                                /*  Port 1 Function Select                              */
#define X_P2SEL     (0x70F5)                                                /*  Port 2 Function Select                              */
#define X_P1INP     (0x70F6)                                                /*  Port 1 Input Mode                                   */
#define X_P2INP     (0x70F7)                                                /*  Port 2 Input Mode                                   */

#define X_U1CSR     (0x70F8)                                                /*  USART 1 Control and Status                          */
#define X_U1DBUF    (0x70F9)                                                /*  USART 1 Receive/Transmit Data Buffer                */
#define X_U1BAUD    (0x70FA)                                                /*  USART 1 Baud Rate Control                           */
#define X_U1UCR     (0x70FB)                                                /*  USART 1 UART Control                                */
#define X_U1GCR     (0x70FC)                                                /*  USART 1 Generic Control                             */
#define X_P0DIR     (0x70FD)                                                /*  Port 0 Direction                                    */
#define X_P1DIR     (0x70FE)                                                /*  Port 1 Direction                                    */
#define X_P2DIR     (0x70FF)                                                /*  Port 2 Direction                                    */

//Flash
#define P_INFOPAGE  (x7800)                                                 /* Pointer to Start of Flash Information Page           */
#define P_XBANK     (0x8000)                                                /* Pointer to Start of Selectable Flash Bank (XBANK)    */

#endif  /*  USING_ECLIPSE  */

#endif /* BSP_TARGETS_SUPPORT_IOCC2541_JMR_H_ */

