#ifndef STOPWATCH_H_
#define STOPWATCH_H_

// ----------- DWT (Data Watchpoint and Trace)  Core Registers -------------------------------

//DWT control registers
#define DWT_CTRL_REG	(*((volatile uint32_t*)0xE0001000))
//DWT cycle counter register
#define DWT_CYCCNT_REG	(*((volatile uint32_t*)0xE0001004))
//Debug Exception and Monitor Control Register
#define DEMCR_REG	(*((volatile uint32_t*)0xE000EDFC))

//Enable bit for DEMCR register
#define DEMCR_ENA_BIT	(1UL<<24)
//Enable bit for DWT cycle counting
#define CYCCNT_ENA_BIT	(1UL<<0)


// ---------- Macro Functions for DWT ---------------------------------------------------------
//Enable DEMCR
#define InitCycleCounter() \
  DEMCR_REG |= DEMCR_ENA_BIT

//Enable Cycle Counter
#define EnableCycleCounter() \
  DWT_CTRL_REG |= CYCCNT_ENA_BIT

//Disable Cycle Counter
#define DisableCycleCounter() \
  DWT_CTRL_REG &= ~CYCCNT_ENA_BIT

//Reset Cycle Counter
#define ResetCycleCounter() \
  DWT_CYCCNT_REG = 0

#define GetCycleCounter() \
  DWT_CYCCNT_REG


// ----------- Stopwatch Functions ------------------------------
void stopwatch_init(void);
void stopwatch_reset(void);
void stopwatch_start(void);
float stopwatch_end(void);

#endif //STOPWATCH_H_
