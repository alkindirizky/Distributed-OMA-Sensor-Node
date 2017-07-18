#ifndef ACC_DRIVER_H_
#define ACC_DRIVER_H_

//------------------- function lists
void accelero_init(void);
void accelero_fifo_poll(float* acc_data);

#endif
