#include <stdio.h>
#include <stdlib.h>

#include "procsetting.h"
#include "common_struct.h"
#include "acc_driver.h"
#include "signal_proc.h"
#include "comm_handler.h"

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
static uint16_t peak_loc[MAX_PEAKNUM] = {0};
static uint16_t peak_num = 0;

//variables for FFT result & 2nd phase peak selection
static float fft_data[NFFT] = {0}; //arranged into real(1), imag(1), real(2), imag(3)..so on
static pinfo peak_info; //contain information about peak area of interest
static uint16_t sel_fft_datacount = 0; //contain how many data are selected (each 32-bit)

// ----- main() ---------------------------------------------------------------
int main(int argc, char* argv[]){
	//state machines
	uint8_t state = S_INIT;
	uint8_t procphase = PHASE1;

	//iteration counter
	uint16_t psd_wincount = 0; //how many psd window processed
	uint16_t phase2_iter_counter = 0; //how many phase cycle elapsed

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
			fft_calc(signal_data, fft_data);
			psd_calc(fft_data, psd_data);
			psd_wincount += 1;

			if(psd_wincount >= PSD_NWINDOW){
				//sufficient window
				psd_wincount = 0;
				state = S_PHASE1_PEAK_SEL;
			}else{
				//need to obtain new window
				state = S_PHASE_SIG_ACQ;
			}
		}
		else if(state == S_PHASE1_PEAK_SEL){
			//selecting peak from PSD data
			peak_num = peak_sel(psd_data, peak_loc);

			state = S_PHASE1_COM;
		}
		else if(state == S_PHASE1_COM){
			//transmit the obtained peaks
			transmit_peakloc(peak_loc, peak_num);

			//wait to receive command from central
			procphase = dummy_receive_check();
			if(procphase == PHASE2){
				dummy_receive_pinfo(&peak_info, peak_loc, peak_num);
			}
			state = S_PHASE_SIG_ACQ;
		}
		else if(state == S_PHASE2_SIG_PROC){
			fft_calc(signal_data, fft_data);
			sel_fft_datacount = fft_sel(fft_data, &peak_info);

			state = S_PHASE2_COM;
		}
		else if(state == S_PHASE2_COM){
			//transmit FFT data
			transmit_fft(fft_data, sel_fft_datacount);

			//increase iteration counter & check
			phase2_iter_counter++;
			if(phase2_iter_counter >= peak_info.numiter){
				phase2_iter_counter = 0;

				//wait to receive command from central
				procphase = dummy_receive_check();
				if(procphase == PHASE2){
					dummy_receive_pinfo(&peak_info, peak_loc, peak_num);
				}

				if(peak_info.numiter == 0){ //for testing
					state = S_SLEEP; //go to sleep
				}
				else{
					state = S_PHASE_SIG_ACQ;
				}
			}
			else{
				state = S_PHASE_SIG_ACQ; //perform next iteration
			}
		}
		else if(state == S_SLEEP){
			/*TODO implement sleep & reactivate strategy here*/
			break;
		}
	}
	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
