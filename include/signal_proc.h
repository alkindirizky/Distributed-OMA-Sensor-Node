#ifndef SIGNAL_PROC_H_
#define SIGNAL_PROC_H_

#include "procsetting.h"

extern uint16_t testing_peakloc[MAX_PEAKNUM]; //todo: erase later;
extern uint16_t testing_peaknum; //todo: erase later;

/* ---------structure for saving peak area -------*/
typedef struct{
	uint16_t start;
	uint16_t end;
} parea;

/* ------------ list of functions ----------------*/
void psd_calc(float* fft_data, float* psd_data);
void fft_calc(float* signal_data, float* fft_data);
uint16_t peak_sel(float* psd_data, parea* peak_area);
uint16_t peak_loc_obtain(float* psd_data, uint16_t* peak_loc);
uint16_t peak_area_obtain(uint16_t* peak_loc, uint16_t peak_num, parea* peak_area);
void smooth(float* input, uint16_t input_len);
void fft_sel(float* fft_data);
float mean_calc(float* input, uint16_t input_len);
float max_calc(float* input, uint16_t input_len);
float min_calc(float* input, uint16_t input_len);

#endif
