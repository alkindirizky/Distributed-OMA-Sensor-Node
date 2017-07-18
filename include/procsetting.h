#ifndef PROC_SETTING_H_
#define PROC_SETTING_H_

//----- Common Includes ---------------------------------------------------
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
#define NFFT 1024
#define PSD_NWINDOW 8

#endif
