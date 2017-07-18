#ifndef SIGNAL_PROC_H_
#define SIGNAL_PROC_H_

#include "procsetting.h"

void psd_calc(float* acc_data, float* psd_data);
void fft_calc(float* acc_data, float* fft_data);
void peak_sel(float* psd_data);
void fft_sel(float* fft_data);

#endif
