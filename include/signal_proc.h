#ifndef SIGNAL_PROC_H_
#define SIGNAL_PROC_H_

#include "procsetting.h"

void psd_calc(float* fft_data, float* psd_data);
void fft_calc(float* signal_data, float* fft_data);
void peak_sel(float* psd_data);
uint16_t peak_loc_obtain(float* psd_data, uint16_t* peak_loc);
void smooth(float* input, uint16_t input_len);
void fft_sel(float* fft_data);
float mean_calc(float* input, uint16_t input_len);
float max_calc(float* input, uint16_t input_len);
float min_calc(float* input, uint16_t input_len);

#endif
