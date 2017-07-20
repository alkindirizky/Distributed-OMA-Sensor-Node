#ifndef PROC_SETTING_H_
#define PROC_SETTING_H_

//----- Common Includes ---------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include <string.h>

//----- States definition --------------------------------------------------
#define S_INIT 1
#define S_PHASE1_SIG_ACQ 2
#define S_PHASE1_SIG_PROC 3
#define S_PHASE1_PEAK_SEL 4
#define S_PHASE1_TRANSMIT 5
#define S_PHASE2_SIG_ACQ 6
#define S_PHASE2_SIG_PROC 7
#define S_PHASE2_TRANSMIT 8

// ----- setting ------------------------------------------------------------
#define SIGNAL_SIZE 2048
#define F_SAMPLING 500

#define NFFT 2048
#define PSD_SIZE NFFT/2
#define PSD_NWINDOW 8
#define SUM_WINDOW 767.6f

#define FIL_ORDER 3
#define FIL_LEN 13

#define PEAK_DOM_DIV 20.00f
#define PEAK_THRESH_MULT 0.4f

#endif
