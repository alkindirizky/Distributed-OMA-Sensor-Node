#ifndef DEBUG_FUNCTIONS_H_
#define DEBUG_FUNCTIONS_H_
#include "procsetting.h"

uint16_t signal_check(float* acc_data);
void signal_print(float* acc_data);
void psd_print(float* psd_data);
void fft_print(float* fft_data);


#endif
