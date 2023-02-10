/*
 * ADC.h
 *
 * Created: 4/14/2021 12:06:54 AM
 *  Author: Akm Islam
 */ 

#ifndef ADC_H_
#define ADC_H_

// Function Prototypes.

//***************************************************************************
//
// Function Name        : "init_adc"
// Date                 : 4/9/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function initializes the ADC to convert analog
//						voltages received from the MCP9700.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void init_adc(void);

//***************************************************************************
//
// Function Name        : "init_adc"
// Date                 : 4/9/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function reads and computes the result of the
//						ADC. The result is scaled to display in Celsius.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void adc_conversion(void);


// Global Variables.
volatile uint16_t ADC_bin;
int8_t celsius[4];
int64_t temp;

#endif /* ADC_H_ */