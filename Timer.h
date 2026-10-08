#ifndef TIMEDELAY_H
#define TIMEDELAY_H

#include <xc.h>
#include <stdint.h>

void TimerInit(void);
void Timer3_Start(uint16_t pr3);
void Timer3_Stop(void);

#endif // TIMEDELAY_H