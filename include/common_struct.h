#ifndef COMMON_STRUCT_H_
#define COMMON_STRUCT_H_
#include <procsetting.h>

typedef struct{ //structure for saving peak area
	uint16_t start;
	uint16_t end;
} parea;

typedef struct{ //structure for saving data acq and selection info
	parea area[MAX_PEAKNUM];
	uint16_t numarea;
	uint16_t numiter;
} pinfo;


#endif /* COMMON_STRUCT_H_ */
