/*
 * main.c
 *
 *  Created on: May 3, 2016
 *      Author: mcruiters
 */


#include <msp430.h>
#include "uart.h"
#include "LED.h"
#include "ADC.h"
#include "timerA.h"

//Prototypes
void ConfigureClockModule(void);

int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	ConfigureClockModule();
	ConfigureTimerA();
	ConfigureADC();
	configureUART();

	// Initialize port pins associated with the LEDs and turn off LEDs.
	//SetLEDState(LED1,OFF);

	__bis_SR_register( GIE); // Enter LPM0, interrupts enabled


}


void ConfigureClockModule(void)
{
/* Use Calibration values for 1MHz Clock DCO*/
	DCOCTL = 0;
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
}

