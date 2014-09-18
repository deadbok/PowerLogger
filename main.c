/*
 * Program from logging power.
 *
 * Unimplented:
 * 	- Timer.
 * 	- ADC sampling.
 * 	- SD card saving.
 *
 * 	Implemented:
 * 	 - Serial output.
 */
#include <msp430.h>
#include "adc.h"
#include "config.h"
#include "clock.h"
#include "itoa.h"
#include "ports.h"
#include "timer.h"
#include "uart.h"

//Variable to store integers as strings
char	tmp_intstr[10];

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    clock_init();
    ports_init();
    uart_init();
    timer_init();
    adc_init();

    //Print welcome banner.
	P1OUT |= TXLED;
	uart_putc("PowerLogger version 0.0.1 by deadbok.\r\n");
	P1OUT &= ~TXLED;


    //Run this code forever, but put the CPU to sleep
    while(1)
    {
    	//Sample
    	adc_sample();
    	//Go to sleep until sampling is done
    	__bis_SR_register(CPUOFF + GIE); //Enter LPM0 + global interrupt enable

    	P1OUT |= TXLED;
    	itoa(temperature, tmp_intstr, 10);
    	uart_putc(tmp_intstr);
    	uart_putc("\r\n");
    	P1OUT &= ~TXLED;

    	__bis_SR_register(CPUOFF + GIE); //Enter LPM0 + global interrupt enable
    }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer_isr(void)
{
	//Keep the processor awake on return
	__bic_SR_register_on_exit(CPUOFF);
}

/*
 * uart_rx_isr
 *
 * ISR for recieving from the UART
 *
 */
//#pragma vector=USCIAB0RX_VECTOR
//__interrupt void uart_rx_isr(void)
//{
//}
