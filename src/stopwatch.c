#include <stdint.h>
#include "stopwatch.h"
#include "diag/Trace.h"

#include "stm32f4xx.h"

static uint32_t tstart = 0;
static uint32_t tend = 0;

//init stopwatch
void stopwatch_init(void){
	InitCycleCounter();
	EnableCycleCounter();
	trace_printf("System Clock Rate: %d Hz\n",SystemCoreClock);
}

//reset the stopwatch
void stopwatch_reset(void){
	tstart = 0;
	tend = 0;
	ResetCycleCounter();
}

//start timer
void stopwatch_start(void){
	tstart = GetCycleCounter();
}

//stop timer, return time as microsecond
float stopwatch_end(void){
	tend = GetCycleCounter();
	float etime = (float)(tend - tstart);
	etime = etime/SystemCoreClock*1000000.00f;

	//reset the stopwatch after result
	stopwatch_reset();
	return etime;
}


