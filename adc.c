/*
 * adc.c
 *
 * Functions for the analog to digital converter.
 *
 *  Created on: 18/09/2014
 *      Author: oblivion
 */
#include <msp430.h>

unsigned int temperature;
/*
 * adc_init
 *
 * Intialize the analog to digital converter.
 */
void adc_init(void)
{
	ADC10CTL1 = INCH_10 + ADC10DIV_3; // Channel 10 (temp sensor), ADC10CLK/4
	// Vcc & Vss as reference, Sample and hold 64 * AD10CLK, ADC10 on, ADC10 interrupt enable
	ADC10CTL0 = SREF_0 + ADC10SHT_3 + ADC10ON + ADC10IE;
	// ADC10AE0 |= BIT5; //P1.5 as ADC input
}

/*
 * adc_sample
 *
 * Sample the ADC input.
 */
void adc_sample(void)
{
	ADC10CTL0 |= ENC + ADC10SC; //Sampling and conversion start
}

/*
 * adc_isr
 *
 * Interrupt service routine called when the ADC is done sampling.
 */
#pragma vector=ADC10_VECTOR
__interrupt void adc_isr(void)
{
	temperature = ADC10MEM; //Save the ADC result
}
