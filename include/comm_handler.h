#ifndef COMM_HANDLER_H_
#define COMM_HANDLER_H_
#include "procsetting.h"
#include "common_struct.h"

#define RTYPE_SETTING 1
#define RTYPE_S_PHASE1 2
#define RTYPE_S_PHASE2 3

#define TTYPE_PEAKLOC 1
#define TTYPE_FFT 2

void transmit_peakloc(uint16_t* peak_loc, uint16_t peak_num);
void transmit_fft(void);
uint8_t dummy_receive_check(void);
void dummy_receive_pinfo(pinfo* peak_info, uint16_t* peak_loc, uint16_t peak_num);

#endif /* COMM_HANDLER_H_ */
