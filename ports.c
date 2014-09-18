/*
 * ports.c
 *
 * Functions for dealing with I/O ports
 *
 *  Created on: 17/09/2014
 *      Author: oblivion
 */
#include <msp430.h>
#include "config.h"
/*
 * ports_init
 *
 * Initialize the ports
 *
 */
void ports_init(void)
{
	//Unused ports set as output
	P2DIR = 0xFF;
	P2OUT &= 0x00;
	P3DIR = 0xFF;
	P3OUT &= 0x00;



	//Set LED pins as output
	P1DIR |= RXLED + TXLED;
	P1OUT &= 0x00;

	//Select serial function for RX and TX pin
	P1SEL |= TXD + RXD;
	P1SEL2 |= TXD + RXD;
}


