/*
 * main.c 
 * 
 * Main source for the Power Logger.
 *
 * Unimplented:
 * 	- Timer.
 * 	- ADC sampling.
 * 	- SD card saving.
 *
 * 	Implemented:
 * 	 - Serial output.
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
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "adc.h"

/*
 * main.c
 */
int main(void) {
    uart_init();
    adc_init();
    
    //Set serial as standard I/O
    stdout = stdin = &uart_stdout;

	printf("PowerLogger version 0.0.1 by deadbok.\r\n");

    //Run this code forever, but put the CPU to sleep
    while(1)
    {
        printf("\nVCC: %u\n", adc_get_vcc());
        printf("Temperature: %u\n", adc_get_temp());
        
        for(unsigned char i = 0; i < 4; i++)
        { 
            printf("Channel %u: %u\n", i, adc_sample(ADC_REF_AVCC, i));
        }
        _delay_ms(1000);
    }
}
