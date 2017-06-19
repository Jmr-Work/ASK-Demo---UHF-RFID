#ifndef LIB_RFID_H_
#define LIB_RFID_H_

//Libraries
#include <stdint.h>
#include <stdbool.h>

//Project
#include "commands.h"


//Typedefs
typedef struct {
    uint32_t arr_ind;
    uint32_t byte_ind;
} dataBitGenLoc;


//Definitions
#define BITS_IN_BYTE        (8)

//Globals
extern dataBitGenLoc rfid_sig_idleRF(uint8_t arr[], dataBitGenLoc loc, uint32_t idleRF_cts, bool cw_on);
extern dataBitGenLoc rfid_sig_dataBit(uint8_t arr[], dataBitGenLoc loc, bool bitVal);

extern dataBitGenLoc rfid_sig_delim(uint8_t arr[], dataBitGenLoc loc);
extern dataBitGenLoc rfid_sig_RTCal(uint8_t arr[], dataBitGenLoc loc);
extern dataBitGenLoc rfid_sig_TRCal(uint8_t arr[], dataBitGenLoc loc);



extern dataBitGenLoc rfid_sig_Query(uint8_t arr[], dataBitGenLoc loc, QueryCommand cmd);
extern dataBitGenLoc rfid_sig_Select(uint8_t arr[], dataBitGenLoc loc, SelectCommand cmd);


#endif /* LIB_RFID_H_ */

