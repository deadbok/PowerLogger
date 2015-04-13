/*
 * adc.c
 *
 * Functions for the analog to digital converter.
 *
 * Copyright 2015 Martin bo Kristensen Grønholdt <oblivion@ace2>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "config.h"

/*
 * adc_init
 *
 * Intialize the analog to digital converter.
 */
void adc_init(void)
{
    //Set prescaler to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

/*
 * adc_sample
 *
 * Sample the ADC input.
 * 
 * Parameters
 *  ref:
 *   Reference voltage.
 *    00000000, AREF, internal V ref turned off
 *    01000000, AVCC with external capacitor at AREF pin
 *    10000000, Reserved
 *    11000000, Internal 1.1V voltage reference with external capacitor at AREF pin
 *  channel:
 *   The channel to sample from.
 *   0b0000 = ADC0
 *   0b0001 = ADC1
 *   0b0010 = ADC2
 *   0b0011 = ADC3
 *   0b0100 = ADC4
 *   0b0101 = ADC5
 *   0b0110 = ADC6
 *   0b0111 = ADC7
 *   0b1000 = ADC8 (Internal temperature sensor)
 *   0b1001 = (reserved)
 *   0b1010 = (reserved)
 *   0b1011 = (reserved)
 *   0b1100 = (reserved)
 *   0b1101 = (reserved)
 *   0b1110 = 1.1V (V BG )
 *   0b1111 = 0V (GND)
 * Return:
 *  The sampled value.
 */
unsigned int adc_sample(unsigned char ref, unsigned char channel)
{        
    /* REFS = 11, internal 1.1V ref.
     * ADLR = 0, right adjusted.
     * Reserverd = 0.
     * MUX = channel.
     */
     ADMUX = (0xF0 & (ref)) | (0x0F & channel);
     
     debug("ADMUX: 0x%X\n", ADMUX);
     //Wait for the new values to sink in.
     _delay_ms(1);
     
    //Start conversion
    ADCSRA |= (1 << ADSC);
    
    //Wait until sampling is done
    while(ADCSRA & (1 << ADSC))
    {
    }
    
    //Return result.
    return(ADC);
}

//From: http://wp.josh.com/2014/11/06/battery-fuel-guage-with-zero-parts-and-zero-pins-on-avr/
unsigned int adc_get_vcc(void)
{
	
	/* Select ADC inputs
     * REFS = 01,  Vcc used as Vref.
     * ADLR = 0, right adjusted.
     * Reserverd = 0.
     * MUX = 1110, 1.1V Internal Ref.
     */
	ADMUX = 0b01001110;
	
	/*
		After switching to internal voltage reference the ADC requires a settling time of 1ms before
		measurements are stable. Conversions starting before this may not be reliable. The ADC must
		be enabled during the settling time.
	*/
		
	_delay_ms(1);
				
	/*
		The first conversion after switching voltage source may be inaccurate, and the user is advised to discard this result.
	*/
	
		
	ADCSRA |= _BV(ADSC);				// Start a conversion
 
 
	while( ADCSRA & _BV( ADSC) ) ;		// Wait for 1st conversion to be ready...
										//..and ignore the result
	 					
		
	/*
		After the conversion is complete (ADIF is high), the conversion result can be found in the ADC
	*/
			
	// Compute a fixed point with 1 decimal place (i.e. 5v= 50)
	//
	// Vcc   =  (1.1v * 1024) / ADC
	// Vcc10 = ((1.1v * 1024) / ADC ) * 10				->convert to 1 decimal fixed point
	// Vcc10 = ((11   * 1024) / ADC )				->simplify to all 16-bit integer math
				
	unsigned int vccx10 = (1126400L / ADC); 
	
	return(vccx10);
}

unsigned int adc_get_temp(void)
{
    unsigned int    temp;    

    //Sample the temperature sensor.
    temp = adc_sample(ADC_REF_AVCC, MUX3);
    
    return(temp);
}
