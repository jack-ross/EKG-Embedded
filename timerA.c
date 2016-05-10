#include "timerA.h"
#include "LED.h"
#include "ADC.h"
#include "uart.h"

unsigned int samples[64];
unsigned char testChar;

void ConfigureTimerA(void)
{
	//Tell the counter to count up, divide by 1, and clear
	TACTL |= TASSEL_2 | ID_0 | MC_1 | TACLR;
	//MCLK @ 1 MHz / 700 = 1428 (rounded up)
	//count up to 8333 ~= 120 Hz | 2048 = 480 Hz | 
	TACCR0 |= 8333;
	//Enable interupts
	TACCTL0 |= CCIE;
}

unsigned int curADCVal = 34;
unsigned int adc_bit0, adc_bit1;
unsigned char adc_bit2, adc_bit3, recieved;
#pragma vector = TIMER0_A0_VECTOR
/* Timer a interrupt service routine
 *
 * Take samples from the ADC channel and filter (average) them
*/

__interrupt void TimerA0_routine(void)
{
		//take sample
		curADCVal = getADCConversion();

		//enable conversion and start next conversion
		ADC10CTL0 |= ENC | ADC10SC;

		// seperate into single bytes for encoding
		adc_bit0 = (curADCVal & 0xF000) >> 12;
		adc_bit1 = (curADCVal & 0x0F00) >> 8;
		adc_bit2 = (curADCVal & 0x00F0) >> 4;
		adc_bit3 = (curADCVal & 0x000F);

		// SPI send char
		uart_putc((unsigned char) adc_bit0);
		uart_putc((unsigned char) adc_bit1);
		uart_putc((unsigned char) adc_bit2);
		uart_putc((unsigned char) adc_bit3);

		// send seperator key using 2 bytes
		uart_putc(0xFF);
}


unsigned int ADCReading;
/*
 *	returns the value obtained from ADC
 *
 */
unsigned int getADCConversion(){
	//wait until the conversion is done
	while(ADC10CTL1 & BUSY);

	ADCReading=ADC10MEM;	//read the register
	ADC10CTL0&=~ENC; 		//Turn off conversion
	
	return ADCReading;
}

unsigned int runningSum =0;
int curSampleIndex =0;
int i;	
/*
 * filter()
 * param : ADC value to add to the running sum/average
 *
 * Can check LED1 to see how fast its firing
 *
 * returns the running average (avg value)
 */
unsigned int filter(unsigned int curADCValue){
	//TURN_ON_LED1;
	
	//Get the next index to add
	//equivalent to i = (i+1) % 64
	curSampleIndex = (curSampleIndex+1) & 63;
	//Subtract the old value that you are about to replace from the sum
	runningSum -=samples[curSampleIndex]; 
	//Replace the value (circular buffer)
	samples[curSampleIndex] = curADCValue;
	//Add it to the sum
	runningSum += samples[curSampleIndex];

	//divide by 64 to get average
	runningAvg = runningSum >> 8;

	//TURN_OFF_LED1;
	return runningAvg;
}


