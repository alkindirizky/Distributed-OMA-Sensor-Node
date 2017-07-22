#include <procsetting.h>
#include "comm_handler.h"
#include "testsetting.h"
#include "diag/Trace.h"

//transmit peak information
void transmit_peakloc(uint16_t* peak_loc, uint16_t peak_num){
	uint8_t payload[MAX_PAYLOAD_SIZE];

	//copy the header
	payload[0] = TTYPE_PEAKLOC; //packet type
	payload[1] = 1; //number of frame
	payload[2] = 0; //frame id
	payload[3] = peak_num; //number of packet

	//copy the data
	memcpy(payload + 4, peak_loc, peak_num*sizeof(uint16_t));

	/*todo send the payload to radio driver*/
}

//transmit fft data
void transmit_fft(float* fft_data, uint16_t fft_datacount){
	uint8_t payload[MAX_PAYLOAD_SIZE];
	uint16_t size_remainder = (fft_datacount*4 + 3) % MAX_PAYLOAD_SIZE;//in byte
	uint16_t num_packet = ((fft_datacount*4 + 3) - size_remainder)/ MAX_PAYLOAD_SIZE;

	for(uint16_t i=0; i<num_packet;i++){
		//copy the header
		payload[0] = TTYPE_PEAKLOC; //packet type
		payload[1] = 1; //number of frame
		payload[2] = i; //frame id

		if(i == num_packet - 1){
			memcpy(payload+3, fft_data, size_remainder*sizeof(uint8_t));
		}
		else{
			memcpy(payload+3, fft_data, (MAX_PAYLOAD_SIZE - 3)*sizeof(uint8_t));
		}

		/*TODO* Transmit here*/
	}

}

//check the type of packet
uint8_t dummy_receive_check(void){
	//currently always return phase 2 for testing
	return PHASE2;
}

//obtain peak info for peak selection
void dummy_receive_pinfo(pinfo* peak_info, uint16_t* peak_loc, uint16_t peak_num){
	const uint16_t pband[3] = {0,PAREA_BAND, PEAK_BAND};
	const uint16_t piter[3] = {0,ITER1, ITER2};
	static uint8_t pband_ind = 0;

	//save the area information
	pband_ind++;
	if(pband_ind<3){
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
}
