#ifndef TIMER_A_H
#define TIMER_A_H

#include <msp430.h>

// Prototypes
void ConfigureTimerA(void);
unsigned int getADCConversion(void);
unsigned int filter(unsigned int curADCValue);
#endif
