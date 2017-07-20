#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "procsetting.h"
#include "acc_driver.h"
#include "signal_proc.h"

#include "stopwatch.h"
#include "debug_functions.h"

//----- GCC Pragmas ------------------------------------------------------
// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


// ----- main variables ------------------------------------------------------
//variables for signal
static float signal_data[SIGNAL_SIZE] = {0};
static uint16_t signal_counter = 0;

//variables for autopsd result & first phase peak selection
static float psd_data[PSD_SIZE] = {0};
static uint16_t psd_wincount = 0;
static parea peak_area[MAX_PEAKNUM] = {0};
static uint16_t peak_area_num = 0;

//variables for FFT result & 2nd phase peak selection
static float fft_data[NFFT] = {0}; //arranged into real(1), imag(1), real(2), imag(3)..so on
static uint16_t info_peakloc[MAX_PEAKNUM] = {0};
static uint16_t info_peaknum = 0;
static parea peak_band[MAX_PEAKNUM] ={0};

// ----- main() ---------------------------------------------------------------
int main(int argc, char* argv[]){
	//state machines
	uint8_t state = S_INIT;
	uint8_t procphase = PHASE1;

	//init stopwatch
	stopwatch_init();

	while(1){
		if(state == S_INIT){
			//init devices
			accelero_init();
			state = S_PHASE_SIG_ACQ;
		}
		else if(state == S_PHASE_SIG_ACQ){
			//polling signal data and update counter
			accelero_fifo_poll(signal_data + signal_counter);
			signal_counter += 32;

			if(signal_counter >= SIGNAL_SIZE){
				signal_counter = 0;
				if(procphase == PHASE1){
					state = S_PHASE1_SIG_PROC;
				}
				else if(procphase == PHASE2){
					state = S_PHASE2_SIG_PROC;
				}
			}
		}
		else if(state == S_PHASE1_SIG_PROC){
			//create autopsd, perform fft first
			//stopwatch_start();
			fft_calc(signal_data, fft_data);
			//trace_printf("fft tcalc (us), %0.3f\n",stopwatch_end());
			//stopwatch_start();
			psd_calc(fft_data, psd_data);
			//trace_printf("psd tcalc (us), %0.3f\n",stopwatch_end());
			psd_wincount += 1;

			if(psd_wincount >= PSD_NWINDOW){
				//sufficient window
				psd_wincount = 0;
				state = S_PHASE1_PEAK_SEL;
			}else{
				//obtain new window
				state = S_PHASE_SIG_ACQ;
			}
		}
		else if(state == S_PHASE1_PEAK_SEL){
			//selecting peak from PSD data
			stopwatch_start();
			peak_area_num = peak_sel(psd_data, peak_area);
			trace_printf("peaksel tcalc (us), %0.3f\n",stopwatch_end());

			parea_print(peak_area, peak_area_num);

			state = S_PHASE1_COM;
		}
		else if(state == S_PHASE1_COM){
			//central instruct to do phase 2
			/*todo : will be replaced by packet handler later*/
			procphase = PHASE2;
			info_peaknum = testing_peaknum;
			memcpy(info_peakloc, testing_peakloc, testing_peaknum*sizeof(uint16_t));

			peak_print(info_peakloc, info_peaknum);
			break;

			state = S_PHASE_SIG_ACQ;
		}
		else if(state == S_PHASE2_SIG_PROC){

		}
		else if(S_PHASE2_COM){

		}
		else{
			trace_printf("state is wrong\n");
		}
	}
	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
