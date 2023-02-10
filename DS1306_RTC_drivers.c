/*
 * DS1306_RTC_drivers.c
 *
 * Created: 4/20/2021 9:50:35 PM
 *  Author: Akm Islam
 */ 

#define F_CPU 4000000
#include <avr/io.h>
#include <util/delay.h>
#include "DS1306_RTC_drivers.h"

//Macros for register addresses
#define READ_Control_Register 0x0F
#define WRITE_Control_Register 0x8F
#define WP_bm 0x00
#define One_Hz_Enable_bm 0x04
#define AIE0_bm 0x01

#define WRITE_Alarm0_Register 0x87
#define READ_Alarm0_Register 0x07

#define WRITE_Time_Date_Start 0x80



void SPI_rtc_ds1306_config(void)
{
	VPORTA.DIR = PIN7_bm | PIN6_bm | PIN4_bm;	//PA7 for /SS, PA6 for SCK, PA5 for MISO, PA4 for MOSI.
	VPORTC.DIR |= PIN1_bm;						//PC2 for Alarm0 interrupt, PC1 for CE.
	VPORTC.DIR &= ~PIN2_bm;
	PORTC.PIN2CTRL = PORT_PULLUPEN_bm | PORT_ISC_FALLING_gc;		//Set Interrupt sense to falling edge (Alarm0 is active low).
	
	SPI0.CTRLB = SPI_SSD_bm | SPI_MODE_3_gc;						//Slave select disabled, and use mode 3 (CPOL = 1, CPHA = 1)
	SPI0.CTRLA = SPI_MASTER_bm | SPI_PRESC_DIV4_gc | SPI_ENABLE_bm;	//Enable host mode, 4MHz /4 (1MHz), and enable the SPI.
	
	return;
}


void write_RTC (unsigned char reg_RTC, unsigned char data_RTC)
{
	uint8_t dummy;
	
	VPORTC.OUT |= PIN1_bm;		//Select RTC
	
	_delay_us(4);	//Delay for 4us (CE to CLK setup time)
	
	//Send register address.
	SPI0.DATA = reg_RTC;								//Write to desired register.
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register.
	
	//Send data byte.
	SPI0.DATA = data_RTC;								//Send data.
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register.
	
	__asm("nop");				// Wait 250ns (4ns needed) for CLK to CE hold time.
	
	VPORTC.OUT &= ~PIN1_bm;		//Unselect RTC.
	
	_delay_us(4);				//Wait 4 ns for CE inactive time.
	
	return;
}


unsigned char read_RTC (char reg_RTC)
{
	uint8_t data;
	
	VPORTC.OUT |= PIN1_bm;		//Select CE
	
	_delay_ms(4);	//Delay for 4us (CE to CLK setup time)
	
	SPI0.DATA = reg_RTC;								//Write to desired register.
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	data = SPI0.DATA;									//Clear DATA register (garbage).
	
	_delay_loop_1(2);	//1500ns delay (800ns needed) for CLK to Data Delay.
	
	SPI0.DATA = data;									//Send data (garbage).
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	data = SPI0.DATA;									//obtain data.
	
	VPORTC.OUT &= ~PIN1_bm;		//Unselect CE
	
	return data;
}


void block_write_RTC(volatile unsigned char *array_ptr, unsigned char strt_addr, unsigned char count)
{
	uint8_t dummy;
	
	VPORTC.OUT |= PIN1_bm;		//Select RTC
	
	_delay_us(4);	//Delay for 4us (CE to CLK setup time)
	
	//Send register address.
	SPI0.DATA = strt_addr;								//Write to desired register.
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register.
	
	//Burst Write operation
	for (unsigned char i = 0; i < count; i++)
	{
		//Send data byte.
		SPI0.DATA = *(array_ptr + i);							//Send data.
		while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
		dummy = SPI0.DATA;									//Clear DATA register.
	}

	
	__asm("nop");				// Wait 250ns (4ns needed) for CLK to CE hold time.
	
	VPORTC.OUT &= ~PIN1_bm;		//Unselect RTC.
	
	_delay_us(4);				//Wait 4 ns for CE inactive time.
	
	return;
}

void block_read_RTC(volatile unsigned char *array_ptr, unsigned char strt_addr, unsigned char count)
{
	uint8_t dummy;
	
	SPI_rtc_ds1306_config();	//Configure SPI to communicate with DS1306.
	
	VPORTC.OUT |= PIN1_bm;		//Select CE
	
	_delay_us(4);	//Delay for 4us (CE to CLK setup time)
	
	SPI0.DATA = strt_addr;								//Write to desired register.
	while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
	dummy = SPI0.DATA;									//Clear DATA register (garbage).
	
	//Burst read operation
	for (unsigned char i = 0; i < count; i++)
	{
		_delay_loop_1(2);	//1500ns delay (800ns needed) for CLK to Data Delay.
		
		SPI0.DATA = dummy;									//Send data (garbage).
		while((SPI0.INTFLAGS & SPI_IF_bm) != SPI_IF_bm) {}	//While the serial transfer is incomplete, loop indefinitely.
		*(array_ptr + i) = SPI0.DATA;						//obtain data.
	}
	
	VPORTC.OUT &= ~PIN1_bm;		//Unselect CE
	
	return;
}

void block_write_read_RTC_test(void)
{
	
	write_RTC(WRITE_Control_Register, WP_bm);	//Write to control register to write.
	block_write_RTC(RTC_time_date_write, WRITE_Time_Date_Start, 7);		//Burst write the time and date.
	block_read_RTC(RTC_time_date_read, Read_Time_Date_Start, 7);		//Burst read the time and date.
	
	return;
}

void configure_DS1306(void)
{	
	SPI_rtc_ds1306_config();
	write_RTC(WRITE_Control_Register, WP_bm);	//Write to control register to write.
	write_RTC(WRITE_Control_Register, One_Hz_Enable_bm);	//Enable 1Hz output.
	
	block_read_RTC(RTC_time_date_read, Read_Time_Date_Start, 7);	//Read time and date.
	block_read_RTC(RTC_AIE0, READ_Alarm0_Register, 4);				//Read Alarm time.	
	
	for (int i = 0; i < 7; i++)
	{
		RTC_time_date_write[i] = RTC_time_date_read[i];	//Transfer contents read from read to write.
	}
	
	block_write_RTC(RTC_time_date_write, WRITE_Time_Date_Start, 7);	//Write time and date.
	block_write_RTC(RTC_AIE0, WRITE_Alarm0_Register, 4);			//Write Alarm time.
		
//	write_RTC(WRITE_Control_Register, AIE0_bm); //Enable Alarm0 interrupts.
	
	return;
}