/*
 * uart.c
 *
 * Functions for the UART (serial port)
 *  Created on: 17/09/2014
 *      Author: oblivion
 */
#include <msp430.h>
/*
 * uart_init
 *
 * Initialize the UART
 *
 */
void uart_init(void)
{
	UCA0CTL1 |= UCSSEL_2; //SMCLK

	//9600 baud
	UCA0BR0 = 104;
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1

	UCA0CTL1 &= ~UCSWRST; // Initialize the USCI state machine

	//IE2 |= UCA0RXIE; //Enable USCI_A0 RX interrupt
}

/*
 *
 * uart_putc
 *
 * Send a string on the serial interface
 *
 */
void uart_putc(char *str)
{
	//Loop until the end of the string
	while (*str != '\0')
	{
		while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
		{
			UCA0TXBUF = *str++;
		}
	}
}

