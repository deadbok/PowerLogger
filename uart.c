/*
 * uart.c
 *
 * Functions for the UART (serial port)
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
 */
 
 //Include configuration.
 #include "config.h"
/* Helper macros for setting the baud rate.
 * 
 * Needs F_CPU and BAUD needs to be defined.
 * The header defines UBRRL_VALUE, UBRRH_VALUE and USE_2X.
 */
#include <util/setbaud.h>
//IO
#include <avr/io.h>
#include "uart.h"
/*
 * uart_init
 *
 * Initialize the UART
 *
 */
void uart_init(void)
{
    //Set the baud rate.
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

//Check and maybe set double speed operation
#if USE_2X
    UCSR0A |= (1 << U2X0);
#else
    UCSR0A &= ~(1 << U2X0);
#endif

    //8-bit data, 1 stop bits.
    UCSR0C = (3 << UCSZ00);
    //Enable RX and TX.
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

/*
 *
 * uart_putc
 *
 * Send a string on the serial interface
 *
 */
void uart_putc(char c, FILE *stream)
{
    if ( c == '\n')
    {
        uart_putc('\r', stream);
    }
    //block until ready.
    while (!(UCSR0A & (1 << UDRE0)))
    {
    };
    
	UDR0 = c;
}

char uart_getc(FILE *stream) 
{
    //block until ready.
    while (!(UCSR0A & (1 << RXC0)))
    {
    };
    return(UDR0);
}

