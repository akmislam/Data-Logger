/*
 * RS232.h
 *
 * Created: 4/14/2021 12:09:04 AM
 *  Author: Akm Islam
 */ 


#ifndef RS232_H_
#define RS232_H_

//***************************************************************************
//
// Function Name        : "init_usart"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function initializes the software USART module
//						to communicate using RS232.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void init_usart (void);

//***************************************************************************
//
// Function Name        : "USART_sw_write"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function sends characters using the software
//						module.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void USART_sw_write(char c);


//***************************************************************************
//
// Function Name        : "USART_sw_write_strings"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function sends strings using the software
//						module. This is meant for the strings to output
//						to the Tera Term.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void USART_sw_write_strings ();

#endif /* RS232_H_ */