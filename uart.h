/*
 * uart.h
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

#ifndef __UART_H_
#define __UART_H_

extern void uart_init(void);
extern void uart_putc(char c, FILE *stream);
extern char uart_getc(FILE *stream);

static FILE uart_stdout = FDEV_SETUP_STREAM(
    uart_putc,
    uart_getc,
    _FDEV_SETUP_RW );

#endif
