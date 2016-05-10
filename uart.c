/*
 * uart.c
 *
 *  Created on: May 3, 2016
 *      Author: mcruiters
 */
#include <msp430.h>
#include "uart.h"

void configureUART(){
	/* Configure Pin Muxing P1.1 RXD and P1.2 TXD */
    P1SEL = BIT1 | BIT2;
    P1SEL2 = BIT1 | BIT2;

    /* Place UCA0 in Reset to be configured */
    UCA0CTL1 = UCSWRST;

    /* Configure */
    UCA0CTL1 |= UCSSEL_2; // SMCLK
    UCA0BR0 = 104; 		// 1MHz 9600
    UCA0BR1 = 0; 		// 1MHz 9600
    UCA0MCTL = UCBRS0; 	// Modulation UCBRSx = 1

    /* Take UCA0 out of reset */
    UCA0CTL1 &= ~UCSWRST;

    /* Enable USCI_A0 RX interrupt */
    IE2 |= UCA0RXIE;	// | UCA0TXIE;

    rx_flag = 0;		//Set rx_flag to 0
}



/*
 * uart_putc
 * Sends a char to the UART. Will wait if the UART is busy
 * INPUT: Char to send
 * RETURN: None
 */
void uart_putc(unsigned char c)
{
    tx_char = c;		// Put the char into the tx_char

    tx_flag = 1;		// Reset the tx_flag
    /* Wait for the transmit buffer to be ready */
	while (!(IFG2 & UCA0TXIFG));

	/* Transmit data */
	UCA0TXBUF = (char ) c;
    return;
}

/*uart_puts
* Sends a string to the UART. Will wait if the UART is busy
* INPUT: Pointer to String to send
* RETURN: None
*/
void uart_puts(char *str)               //Sends a String to the UART.
{
     while(*str) uart_putc(*str++);     //Advance though string till end
     return;
}

#pragma vector = USCIAB0TX_VECTOR       //UART TX USCI Interrupt
__interrupt void USCI0TX_ISR(void)
{
  //  UCA0TXBUF = tx_char;                //Copy char to the TX Buffer
    tx_flag = 0;                        //ACK the tx_flag
    //IE2 &= ~UCA0TXIE;                   //Turn off the interrupt to save CPU
}

// Echo back RXed character, confirm TX buffer is ready first
//This routine is run for every char in the TX buffer
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    while (!(IFG2&UCA0TXIFG)); // USCI_A0 TX buffer ready?
    static unsigned char curChar, recieved, test = 100;
    //must store the rx buffer to pass this while loop ^
    recieved = UCA0RXBUF; // TX -&amp;gt; RXed character

}


