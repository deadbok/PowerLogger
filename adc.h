/*
 * adc.h
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

#ifndef __ADC_H_
#define __ADC_H_

//Defines for selecting the reference for the conversion
#define ADC_REF_AREF    0b00000000 //AREF, internal V ref turned off
#define ADC_REF_AVCC    0b01000000 //AVCC with external capacitor at AREF pin
#define ADC_REF_11V     0b11000000 //Internal 1.1V voltage reference with external capacitor at AREF pin

extern void adc_init(void);
extern unsigned int  adc_sample(unsigned char ref, unsigned char channel);

extern unsigned int adc_get_vcc(void);
extern unsigned int adc_get_temp(void);

#endif
