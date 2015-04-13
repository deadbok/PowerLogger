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

/*
 * adc_init
 *
 * Intialize the analog to digital converter.
 */
void adc_init(void)
{
}

/*
 * adc_sample
 *
 * Sample the ADC input.
 */
void adc_sample(void)
{
}

//From: http://wp.josh.com/2014/11/06/battery-fuel-guage-with-zero-parts-and-zero-pins-on-avr/
unsigned int adc_get_vcc(void)
{
	
	// Select ADC inputs
	// bit    76543210 
	// REFS = 00       = Vcc used as Vref
	// MUX  =   100001 = Single ended, 1.1V (Internal Ref) as Vin
	
	ADMUX = 0b01001110;
	
	/*
	By default, the successive approximation circuitry requires an input clock frequency between 50
	kHz and 200 kHz to get maximum resolution.
	*/	
				
     //set prescaller to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);

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
	
	/*	
		Note that the ADC will not automatically be turned off when entering other sleep modes than Idle
		mode and ADC Noise Reduction mode. The user is advised to write zero to ADEN before entering such
		sleep modes to avoid excessive power consumption.
	*/
	
	ADCSRA &= ~_BV( ADEN );			// Disable ADC to save power
	
	return(vccx10);
}

long adc_get_temp(void)
{
    long    temp;
    
    //set prescaller to 128 and enable ADC 
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
    
    /* REFS = 11, internal 1.1V ref.
     * ADLR = 0, right adjusted.
     * Reserverd = 0.
     * MUX = 1000, ADC8 internal temperature.
     */
     ADMUX = 0b11001000;
     
     //Wait for the new values to sink in.
     _delay_ms(2);
     
    //Start conversion
    ADCSRA |= (1 << ADSC);
    
    //Wait until sampling is done
    while(ADCSRA & (1 << ADSC))
    {
    }
    
    //Store result.
    temp = ADC;
    
    return(temp);
}
