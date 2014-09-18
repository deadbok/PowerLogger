/*
 * clock.c
 *
 * Clock functions.
 *
 *  Created on: 17/09/2014
 *      Author: oblivion
 */
#include <msp430.h>
/*
 * clock_init
 *
 * Initialize the clock
 *
 */
void clock_init(void)
{
	//Set the internal oscillator at 1MHz
	DCOCTL = 0; //Select the lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ; //Set DCO
	DCOCTL = CALDCO_1MHZ;
}

