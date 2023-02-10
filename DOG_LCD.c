/*
 * DOG_LCD.c
 *
 * Created: 4/14/2021 12:06:21 AM
 *  Author: Akm Islam
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "DOG_LCD.h"

void lcd_spi_transmit_CMD(unsigned char cmd)
{
	uint8_t dummy;
	
	VPORTC.OUT &= ~PIN0_bm;								//RS = 0 for command.
	VPORTA.OUT &= ~PIN7_bm;								//Select LCD as client.
	
	SPI0.DATA = cmd;									//Send command.
	
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register.
	
	VPORTA.OUT |= PIN7_bm;	//Deselect LCD as client.
	
	return;
}


void lcd_spi_transmit_DATA (unsigned char cmd)
{
	uint8_t dummy;
	
	VPORTC.OUT |= PIN0_bm;								//RS = 1 for data.
	VPORTA.OUT &= ~PIN7_bm;								//Select LCD as client.

	SPI0.DATA = cmd;									//Send command.
	
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register.
	
	VPORTA.OUT |= PIN7_bm;	//Deselect LCD as client.
	
	return;
}


void init_spi_lcd (void)
{
	uint8_t dummy;
	
	VPORTA.DIR = PIN7_bm | PIN6_bm | PIN4_bm;	//PA7 for /SS, PA6 for SCK, PA5 for MISO, PA4 for MOSI.
	VPORTC.DIR = PIN0_bm;						//PC0 for RS of LCD.
	
	SPI0.CTRLB = SPI_SSD_bm | SPI_MODE_3_gc;	//Slave select disabled, and use mode 3 (1,1).
	SPI0.CTRLA = SPI_MASTER_bm | SPI_CLK2X_bm | SPI_PRESC_DIV4_gc | SPI_ENABLE_bm;		//Enable host mode, 4MHz * 2 / 4 (2MHz), and enable the SPI.
	
	return;
}


void init_lcd_dog (void)
{
	init_spi_lcd();		//Initialize MCU for LCD SPI.
	
	//start_dly_40ms
	_delay_ms(40);		//Startup delay.
	
	//func_set1:
	lcd_spi_transmit_CMD(0x39);		//Send function set #1.
	_delay_us(30);					//Delay for command to be processed.
	
	//func_set2:
	lcd_spi_transmit_CMD(0x39);		//Send function set #1.
	_delay_us(30);					//Delay for command to be processed.
	
	//bias_set:
	lcd_spi_transmit_CMD(0x1E);		//Set Bias value.
	_delay_us(30);					//Delay for command to be processed.
	
	//power_ctrl:
	lcd_spi_transmit_CMD(0x55);		//~ 0x55 for 3.3V (0x50 for 5V).
	_delay_us(30);
	
	//follower_ctrl:
	lcd_spi_transmit_CMD(0x6C);		//Follower mode on.
	_delay_ms(200);					//Delay for command to be processed.
	
	//contrast_set:
	lcd_spi_transmit_CMD(0x7F);		//~ 0x7F for 3.3V (0x77 for 5V).
	_delay_us(30);					//Delay for command to be processed.
	
	//display_on:
	lcd_spi_transmit_CMD(0x0C);		//Display on, cursor off, blink off.
	_delay_us(30);					//Delay for command to be processed.
	
	//clr_display:
	lcd_spi_transmit_CMD(0x01);		//Clear display, cursor home.
	_delay_us(30);					//Delay for command to be processed.
	
	//entry_mode:
	lcd_spi_transmit_CMD(0x06);		//Clear display, cursor home?
	_delay_us(30);					//Delay for command to be processed.
	
	return;
}


void update_lcd_dog(void)
{
	init_spi_lcd();		//Initialize SPI0 for LCD.
	
	lcd_spi_transmit_CMD(0x80);		//Initialize DDRAM address-ctr.
	_delay_us(30);					//Delay for command to be processed.
	
	//Send first line to LCD module.
	for (int i = 0; i < 16; i++)
	{
		lcd_spi_transmit_DATA(dsp_buff1[i]);	//Send ith char of line.
		_delay_us(30);							//Delay for data to be processed.
	}
	
	//Send second line to LCD module.
	for (int i = 0; i < 16; i++)
	{
		lcd_spi_transmit_DATA(dsp_buff2[i]);	//Send ith char of line.
		_delay_us(30);							//Delay for data to be processed.
	}
	
	//Send third line to LCD module.
	for (int i = 0; i < 16; i++)
	{
		lcd_spi_transmit_DATA(dsp_buff3[i]);	//Send ith char of line.
		_delay_us(30);							//Delay for data to be processed.
	}
	
	return;
}