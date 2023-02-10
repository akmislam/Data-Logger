/*
 * ADC.c
 *
 * Created: 4/14/2021 12:08:24 AM
 *  Author: Akm Islam
 */ 
#include <avr/io.h>
#include "ADC.h"

void init_adc(void)
{
	VPORTD.DIR &= ~PIN6_bm;										//Set PD6 as input.
	VREF.ADC0REF = VREF_ALWAYSON_bm | VREF_REFSEL_2V500_gc;		//Turn ADC0 to always on, and use 2.5V reference.
	ADC0.CTRLA = ADC_RESSEL_12BIT_gc;							//Use 12-bit resolution for ADC0.
	ADC0.CTRLC = 0x00;											//Use CLK_PER/2 (default). ADC0 will sample 4/fCLK_PER (p.498).
	ADC0.MUXPOS = ADC_MUXPOS_AIN6_gc;							//MUX select AIN6 (PD6) for ADC0.
	ADC0.CTRLA |= ADC_ENABLE_bm;								//Enable ADC0.
	
	return;
}

void adc_conversion(void)
{
	ADC0.COMMAND = ADC_STCONV_bm;				//Start ADC conversion.
	while ((ADC0.COMMAND & PIN0_bm) == 1) {};	//While ADC is still converting, loop indefinitely.
	ADC_bin = ADC0.RES;							//Store ADC result in ADC_bin.
	
	__asm("nop");
	__asm("nop");
	__asm("nop");
	temp = ADC_bin;
	
	if (ADC_bin < 0x334)	//Negative temperature conversion block.
	{
//		temp = ADC_bin;								//Send to temp to compute temperature.
		temp *= 2500;								//Type cast to 32 bits and multiply by 2500.
		temp >>= 12;								//Divide by 4096 (2^12).
		temp -= 500;								//Subtract 500 for offset.
		
		temp *= -1;
		
		//BCD conversion
		celsius[3] = temp / 1000;					//Divide by 1000, keep integer part (hundreds value).
		temp = temp % 1000;							//Mod by 1000, keep remainder part.
		celsius[2] = temp / 100;					//Divide by 100, keep integer part (tens value).
		temp = temp % 100;							//Mod by 100, keep remainder part.
		celsius[1] = temp / 10;						//Divide by 10, keep integer part (ones value).
		temp = temp % 10;							//Mod by 10, keep remainder part.
		celsius[0] = temp;							//Divide by 1, keep integer part (tenths value).
	}
	
	
	else	//Positive temperature conversion block.
	{
		//Temperature Conversion
		temp = ADC_bin;								//Send to temp to compute temperature.
		temp = (uint32_t)ADC_bin * 2500;			//Type cast to 32 bits and multiply by 2500.
		temp >>= 12;								//Divide by 4096 (2^12).
		temp -= 500;								//Subtract 500 for offset.
	
		//BCD conversion
		celsius[3] = temp / 1000;					//Divide by 1000, keep integer part (hundreds value).
		temp = temp % 1000;							//Mod by 1000, keep remainder part.
		celsius[2] = temp / 100;					//Divide by 100, keep integer part (tens value).
		temp = temp % 100;							//Mod by 100, keep remainder part.
		celsius[1] = temp / 10;						//Divide by 10, keep integer part (ones value).
		temp = temp % 10;							//Mod by 10, keep remainder part.
		celsius[0] = temp;							//Divide by 1, keep integer part (tenths value).
	}
	
	return;
}