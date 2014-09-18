/*
 * timer.c
 *
 * Timer functions.
 *
 *  Created on: 17/09/2014
 *      Author: oblivion
 */
#include <msp430.h>

/*
 * timer_init
 *
 * Initialize timer
 */
void timer_init(void)
{
	CCTL0 = CCIE; //Enable CCR0 interrupt
	TACTL = TASSEL_2 + MC_1 + ID_3; //SMCLK/8, up mode
	CCR0 = 10000; // 12.5Hz. (SMCLK/8)/CCR0.
}
