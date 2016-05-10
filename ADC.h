#ifndef ADC_H
#define ADC_H
#include <msp430.h>

// Use the following to select either analog channel 7 or the temperature sensor
#define ADC10_A0 1
#define ADC10_TEMP_SENSOR 0
#define ADC10_MODE 1

extern unsigned char testChar;
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                 ADC10 A7
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.7
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define ADC10_A0_BIT	BIT0	// Port pin bit location for ADC10 A7


// Prototypes
void ConfigureADC(void);


#endif
