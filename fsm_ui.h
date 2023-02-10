/*
 * fsm_ui.h
 *
 * Created: 4/28/2021 12:17:11 AM
 *  Author: Akm Islam
 */ 


#ifndef FSM_UI_H_
#define FSM_UI_H_

//Functions for each state (outputs of FSM).

//***************************************************************************
//
// Function Name        : "error_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function displays an error has occurred.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void error_fn();				//Incorrect input


//***************************************************************************
//
// Function Name        : "set_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function displays the time.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void set_fn();				//Set hours, minutes, or seconds


//***************************************************************************
//
// Function Name        : "set_hours_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function gets ready to accept hours.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void set_hours_fn();			//Set hours


//***************************************************************************
//
// Function Name        : "set_minutes_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function gets ready to accept minutes.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void set_minutes_fn();		//Set minutes


//***************************************************************************
//
// Function Name        : "set_seconds_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function gets ready to accept seconds.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void set_seconds_fn();		//Set seconds


//***************************************************************************
//
// Function Name        : "enter_hour_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function enters hours.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void enter_hour_fn();		//Enter hours


//***************************************************************************
//
// Function Name        : "enter_minutes_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function enters minutes.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void enter_minute_fn();		//Enter minutes


//***************************************************************************
//
// Function Name        : "enter_seconds_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function enters seconds.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void enter_second_fn();		//Enter seconds


//***************************************************************************
//
// Function Name        : "digit_in_fn"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function enters new digits into the digit
//						buffer.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
extern void digit_in_fn();			//Enter digits

//Enumeration of keys and states.
typedef enum {s, h, m, c, digit, enter, eol} key;			//Enumeration of possible entries.
typedef enum {idle, set, hours, minutes, seconds} state;	//Enumeration of possible states.

//Global variables
volatile unsigned char digit_val;	//Global variable to hold digit value.
state present_state;				//Global variable to hold present state.
char lines[20];						//Lines to display in tera term.
volatile uint8_t digit_buffer[4];	//Buffer to hold digit values.



//***************************************************************************
//
// Function Name        : "fsm"
// Date                 : 4/29/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function maintains the FSM. Table search is
//						implemented using the present state to look into the
//						table, as well as the input entered.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void fsm (state ps, key keyval);	//Prototype for fsm

#endif /* FSM_UI_H_ */