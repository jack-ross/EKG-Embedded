#include "LED.h"

void InitializeLEDPortPins(void)
{
	// Set the LEDs as outputs
	//SET_LED1_AS_AN_OUTPUT;
	//SET_LED2_AS_AN_OUTPUT;

}
void SetLEDState(char choice, char state)
{
	switch (choice) {
		case LED1:
			if (state)
				TURN_ON_LED1;
			else
				TURN_OFF_LED1;
			break;
		case LED2:
			if (state)
				TURN_ON_LED2;
			else
				TURN_OFF_LED2;
			break;
		default:
			break;
	}
	return;
}

void TimeDelay(unsigned int delay, unsigned int resolution)
{
/* The elapsed time for the inner loop represents the period of the unit
 * time increment (such as 1 microsecond or 1 millisecond). The outer loop
 * then represents the total elapsed time in unit time increments
 */
 	unsigned int i,j;

	for (i = 0; i < delay; i++) {
		for (j = 0; j < resolution; j++);
	}
}

