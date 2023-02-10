/*
 * RS232.c
 *
 * Created: 4/14/2021 12:07:05 AM
 *  Author: Akm Islam
 */ 

#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#define BAUD_RATE 9600
#define BIT_PERIOD 1000000/BAUD_RATE
#include "RS232.h"
#include "fsm_ui.h"

void init_usart(void)
{
	USART3.BAUD = (64/16)*(F_CPU/BAUD_RATE);		//Setting BAUD rate (p.376) (5000/3 is more precise).
	USART3.CTRLA = USART_RXCIE_bm;					//Enable RX interrupt (p. 395).
	USART3.CTRLB |= USART_RXEN_bm;	//USART transmitter and receiver are enabled (p.397).
	USART3.CTRLC |= USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_SBMODE_1BIT_gc | USART_CHSIZE_8BIT_gc;
	//Set CTRLC to Asynchronous, No parity, 1 Stop bit, 8 Data bits (p.399).
	
	VPORTB.DIR = 0x01;					//Set PB0 (TX pin) as output and PB1 (RX pin) as input.
	PORTB.PIN1CTRL |= PORT_PULLUPEN_bm;	//Enable pull-up resistor.
	
	
	sprintf(lines, "Welcome");
	USART_sw_write_strings();
	
	sprintf(lines, "Press:");
	USART_sw_write_strings();
	
	sprintf(lines, "s to set the time");
	USART_sw_write_strings();
	
	sprintf(lines, "h to set the hours");
	USART_sw_write_strings();
	
	sprintf(lines, "m to set the minutes");
	USART_sw_write_strings();
	
	sprintf(lines, "c to set the seconds");
	USART_sw_write_strings();
	
	sprintf(lines, "# to set the number");
	USART_sw_write_strings();
	
	return;
}

void USART_sw_write(char c)
{
	//1 -> 0 transition will start transmission.
	VPORTB.OUT = PIN0_bm;	//PB0 is 1.
	_delay_us(BIT_PERIOD);	//Wait bit period.
	VPORTB.OUT = ~PIN0_bm;	//PB0 is 0.
	
	//Transmit each bit from 0 to 7.
	for (int i = 0; i < 8; i++)
	{
		_delay_us(BIT_PERIOD);			//Wait bit period.
		VPORTB.OUT = (PIN0_bm & c);		//Output data bit.
		c >>= 1;						//Right shift bits.
	}
	
	//Stop bit.
	_delay_us(BIT_PERIOD);	//Wait bit period.
	VPORTB.OUT = PIN0_bm;	//Stop bit is set, transmission is complete.
	
	return;
}

void USART_sw_write_strings ()
{
	for (int i = 0; i < 20; i++)
	{
		USART_sw_write(lines[i]);	//Send all char in line.
	}
	
	USART_sw_write(' ');	//Print space.
	
	
	USART_sw_write(10);		//Print CR.
	USART_sw_write(13);		//Print LF.
	
	for (int i = 0; i < 20; i++)
	{
		lines[i] = ' ';	//Clear contents of string
	}
	return;
}