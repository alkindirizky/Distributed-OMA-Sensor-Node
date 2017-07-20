#ifndef DEBUG_FUNCTIONS_H_
#define DEBUG_FUNCTIONS_H_
#include "procsetting.h"
#include "signal_proc.h"

uint16_t signal_check(float* acc_data);
void signal_print(float* acc_data);
void psd_print(float* psd_data);
void fft_print(float* fft_data);
void peak_print(uint16_t* peak_loc, uint16_t peak_num);
void parea_print(parea* peak_area, uint16_t peak_num);

#endif
