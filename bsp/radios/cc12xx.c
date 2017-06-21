/************************************************************************************************************************************/
/** @file       cc12xx.c
 *  @brief      library for Uhf-Id control of the CC1200
 *  @details    this is the working configuration & control code developed by Justin for CC1200 use. This is targeted for extension
 *              to use with the CC1175 but has not been yet verified
 *
 *  @supported  CC1200
 *  @open       CC1175
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
#include "cc12xx.h"
