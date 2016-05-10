/*
 * uart.h
 *
 *  Created on: May 3, 2016
 *      Author: mcruiters
 */

#ifndef UART_H_
#define UART_H_


volatile unsigned int tx_flag;          //Mailbox Flag for the tx_char.
volatile unsigned char tx_char;         //This char is the most current char to go into the UART

volatile unsigned int rx_flag;          //Mailbox Flag for the rx_char.
volatile unsigned char rx_char;         //This char is the most current char to come out of the UART


#define LED BIT0

void configureUART();
void uart_putc(unsigned char c);
void uart_puts(char *str);


#endif /* UART_H_ */
