#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"

#include "procsetting.h"
#include "acc_driver.h"

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

//variables for autopsd result
static float psd_data[NFFT] = {0};
static uint16_t psd_wincount = 0;

//variables for FFT result
static float fft_data[NFFT] = {0};

// ----- main() ---------------------------------------------------------------
int main(int argc, char* argv[]){
	//state machines
	uint8_t state = S_INIT;

	while(1){
		if(state == S_INIT){
			//init devices
			accelero_init();
			state = S_PHASE1_SIG_ACQ;
		}
		else if(state == S_PHASE1_SIG_ACQ){
			//polling signal data and update counter
			accelero_fifo_poll(signal_data + signal_counter);
			signal_counter += 32;

			if(signal_counter >= SIGNAL_SIZE){
				/*debug
				uint16_t fault_count = 0;
				fault_count = signal_check(signal_data);
				if(fault_count>0){
					trace_printf("data inconsistency, number of fault : %d\n",fault_count);
				}
				else{
					trace_printf("data correct, data size : %d\n",signal_counter);
					//signal_print(signal_data);
				}*/

				signal_counter = 0;
				state = S_PHASE1_SIG_PROC;
			}
		}
		else if(state == S_PHASE1_SIG_PROC){
			//create autopsd
			//PSD FUNCTION HERE
			psd_wincount += 1;

			if(psd_wincount >= PSD_NWINDOW){
				psd_wincount = 0;
				state = S_PHASE1_PEAK_SEL;
			}

		}
		else if(state == S_PHASE1_PEAK_SEL){

		}
		else if(state == S_PHASE1_TRANSMIT){

		}
		else if(state == S_PHASE2_SIG_ACQ){

		}
		else if(state == S_PHASE2_SIG_PROC){

		}
		else if(S_PHASE2_TRANSMIT){

		}
		else{
			trace_printf("state is wrong\n");
		}
	}
	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
