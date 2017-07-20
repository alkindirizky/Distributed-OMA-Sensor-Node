#include <stdlib.h>
#include "comm_handler.h"
#include "testsetting.h"

//transmit peak information
void transmit_peakloc(uint16_t* peak_loc, uint16_t peak_num){
	uint8_t* payload;
	payload = (uint8_t*) malloc(peak_num*sizeof(uint16_t) + 1);

	//information about type of package
	payload[0] = TTYPE_PEAKLOC;
	uint8_t pload_ind = 1;
	for(uint16_t i = 0; i<peak_num; i++){
		payload[pload_ind] = peak_loc[i] & 0xff; //LSB
		payload[pload_ind+1] = peak_loc[i] >> 8;
		pload_ind += 2;
	}

	/*todo send the payload to radio driver*/
}

//transmit fft data
void transmit_fft(void){

}

//check the type of packet
uint8_t dummy_receive_check(void){
	//currently always return phase 2 for testing
	return PHASE2;
}

//obtain peak info for peak selection
void dummy_receive_pinfo(pinfo* peak_info, uint16_t* peak_loc, uint16_t peak_num){
	const uint16_t pband[2] = {PAREA_BAND, PEAK_BAND};
	const uint16_t piter[2] = {ITER1, ITER2};
	static uint8_t pband_ind = 0;

	//save the area information
	if(pband_ind<2){
		for(int16_t i=0; i<peak_num; i++){
			peak_info->area[i].start = peak_loc[i] - pband[pband_ind]/2;
			peak_info->area[i].end = peak_loc[i] + pband[pband_ind]/2;
		}
		peak_info->numarea = peak_num;
		peak_info->numiter = piter[pband_ind];
	}
	else{
		peak_info->numiter = 0; //break the test
		pband_ind = 0;
	}
	pband_ind++;
}
