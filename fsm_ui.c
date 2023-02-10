/*
 * fsm_ui.c
 *
 * Created: 4/28/2021 12:16:55 AM
 *  Author: Akm Islam
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "fsm_ui.h"
#include "DS1306_RTC_drivers.h"
#include "RS232.h"
#include <stdio.h>

//Declare pointer type for these functions
typedef void (* task_fn_ptr) ();

//Define structure for state tables
typedef struct {
	key keyval;
	state next_state;
	task_fn_ptr tf_ptr;
} transition;


//Subtable for idle state
const transition idle_transitions [] =
{
	//Input		//Next state	//Output (function)
	{s,			set,			set_fn},
	{eol,		idle,			error_fn},
};

//Subtable for set state
const transition set_transitions [] =
{
	//Input		//Next state	//Output (function)
	{h,			hours,			set_hours_fn},
	{m,			minutes,		set_minutes_fn},
	{c,			seconds,		set_seconds_fn},
	{eol,		idle,			error_fn}
};

//Subtable for hours state
const transition hours_transitions [] =
{
	//Input		//Next state	//Output (function)
	{digit,		hours,			digit_in_fn},
	{s,			set,			set_fn},
	{enter,		idle,			enter_hour_fn},
	{eol,		idle,			error_fn}
};

//Subtable for minutes state
const transition minutes_transitions [] =
{
	//Input		//Next state	//Output (function)
	{digit,		minutes,		digit_in_fn},
	{s,			set,			set_fn},
	{enter,		idle,			enter_minute_fn},
	{eol,		idle,			error_fn}
};

//Subtable for seconds state
const transition seconds_transitions [] =
{
	//Input		//Next state	//Output (function)
	{digit,		seconds,		digit_in_fn},
	{s,			set,			set_fn},
	{enter,		idle,			enter_second_fn},
	{eol,		idle,			error_fn}
};

//Pointer to transitions
const transition * RTC_transitions_ptr[5] =
{
	idle_transitions,
	set_transitions,
	hours_transitions,
	minutes_transitions,
	seconds_transitions
};


void fsm (state ps, key keyval)
{
	int i;
	for (i = 0; (RTC_transitions_ptr[ps][i].keyval != keyval) && (RTC_transitions_ptr[ps][i].keyval != eol); i++)
	{
		//The search will look into the present state, and i will increment until the key value is found.
		//i will hold the position in the subtable which contains the next state and output.
	}
	
	RTC_transitions_ptr[ps][i].tf_ptr();	//Perform task according to transition table.
	
	present_state = RTC_transitions_ptr[ps][i].next_state;	//Present state gets the next state.
	
	return;
}


//Error function: does nothing, returns back to idle state.
extern void error_fn()
{
	sprintf(lines, "Invalid keystroke.");
	USART_sw_write_strings();
	return;
}


//Set function: gets ready to set hours/minutes/seconds.
void set_fn()
{
	volatile uint8_t sample[4];
	
	sample[0] = RTC_time_date_read[0];
	sample[1] = RTC_time_date_read[1];
	sample[2] = RTC_time_date_read[2];
	sample[3] = RTC_time_date_read[3];
	 
	sprintf(lines, "Time %1d%1d:%1d%1d:%1d%1d",  (sample[2] >>= 4) & (0x03), sample[2] & (0x0F) , (sample[1] >>= 4) & (0x0F), sample[1] & (0x0F) , (sample[0] >>= 4) & (0x0F), sample[0] & (0x0F));
	USART_sw_write_strings();

	return;
}


//Set hours function: sets the hours.
void set_hours_fn()
{
	sprintf(lines, "Enter hours: ");
	USART_sw_write_strings();
	
	return;
}


//Set minutes function: sets the minutes.
void set_minutes_fn()
{
	sprintf(lines, "Enter minutes: ");
	USART_sw_write_strings();

	return;
}


//Set seconds function: sets the seconds.
void set_seconds_fn()
{
	sprintf(lines, "Enter seconds: ");
	USART_sw_write_strings();
	return;
}


//Enter hours function: enters the hours.
void enter_hour_fn()
{
	volatile uint8_t digits;
	
	digits = (digit_buffer[1] << 4) | (digit_buffer[0]);	//Create value to enter into location.
	
	write_RTC(0x82, digits);	//Write to hours, using data digits.

//	RTC_time_date_read[2] = digits;

	sprintf(lines, "Entered hours.");
	USART_sw_write_strings();
	return;
}


//Enter minutes function: enters the minutes.
void enter_minute_fn()
{
	volatile uint8_t digits;
	
	digits = (digit_buffer[1] << 4) | (digit_buffer[0]);	//Create value to enter into location.
	
	write_RTC(0x81, digits);	//Write to minutes, using data digits.
	
//	RTC_time_date_read[1] = digits;
	sprintf(lines, "Entered minutes.");
	USART_sw_write_strings();
	return;
}


//Enter seconds function: enters the seconds.
void enter_second_fn()
{
	volatile uint8_t digits;
	
	digits = (digit_buffer[1] << 4) | (digit_buffer[0]);	//Create value to enter into location.

//	RTC_time_date_read[0] = digits;	
	
	write_RTC(0x80, digits);	//Write to seconds, using data digits.
	
	sprintf(lines, "Entered seconds.");
	USART_sw_write_strings();

	return;
}


//Digit in function: enters the digits.
void digit_in_fn()
{
	//shift all digits in buffer.
	digit_buffer[3] = digit_buffer[2];
	digit_buffer[2] = digit_buffer[1];
	digit_buffer[1] = digit_buffer[0];
	
	digit_buffer[0] = digit_val; 
	
	return;
}