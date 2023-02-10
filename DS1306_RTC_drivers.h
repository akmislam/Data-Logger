/*
 * DS1306_RTC_drivers.h
 *
 * Created: 4/20/2021 9:50:54 PM
 *  Author: Akm Islam
 */ 


#ifndef DS1306_RTC_DRIVERS_H_
#define DS1306_RTC_DRIVERS_H_

#define Read_Time_Date_Start 0x00
#define WRITE_Status_Register 0x90
#define WRITE_Alarm0_Register 0x87
#define READ_Alarm0_Register 0x07

//Global Variables
volatile unsigned char RTC_time_date_write[7];// = {0x00, 0x40, 0x14, 0x06, 0x23, 0x04, 0x21};
volatile unsigned char RTC_time_date_read[7];
volatile unsigned char RTC_AIE0[4];// = {0x81, 0x80, 0x80, 0x80};	//Values to set alarm0 every second.


//******************************************************************************
// Function : void SPI_rtc_ds1306_config (void)
// Date and version : 041221, version 1.0
// Target MCU : AVR128 @ 4MHz4
// Author : Akm Islam
// DESCRIPTION
// This function unselects the ds_1306 and configures an AVR128DB48 operated at
// 4 MHz to communicate with the ds1306. Pin PC1 of the AVR128DB48 is used to
// select the ds_1306. SCLK is operated a the maximum possible frequency for
// the ds1306.
//******************************************************************************
void SPI_rtc_ds1306_config(void);


//***************************************************************************
// Function :
// void write_RTC (unsigned char reg_RTC, unsigned char data_RTC)
//
// Target MCU : AVR128DB48 @ 4MHz
// Target Hardware ;
// Author : Akm Islam
// DESCRIPTION
// This function writes data to a register in the RTC. To accomplish this, it
// must first write the register's address (reg_RTC) followed by writing the
// data (data_RTC). In the DS1306 data sheet this operation is called an SPI
// single-byte write.
//**************************************************************************
void write_RTC (unsigned char reg_RTC, unsigned char data_RTC);


//***************************************************************************
// Function Name :
// unsigned char read_RTC (unsigned char reg_RTC)
// Target MCU : AVR128DB48 @ 4MHz
// Author : Akm Islam
// DESCRIPTION
// This function reads data from a register in the RTC. To accomplish this, it
// must first write the register's address (reg_RTC) followed by writing a dummy
// byte to generate the SCLKs to read the data (data_RTC). In the DS1306 data
// sheet this operation is called am SPI single-byte read.
//**************************************************************************
unsigned char read_RTC (char reg_RTC);


//***************************************************************************
// Function Name	: "block_write_RTC"
//					void block_write_RTC (volatile unsigned char *array_ptr,
//					unsigned char strt_addr, unsigned char count)
// Target MCU		: AVR128DB48 @ 4MHz
// Author			: Akm Islam
// DESCRIPTION
// This function writes a block of data from an array to the DS1306. strt_addr
// is the starting address in the DS1306. count is the number of data bytes to
// be transferred and array_ptr is the address of the source array.
//**************************************************************************
void block_write_RTC(volatile unsigned char *array_ptr, unsigned char strt_addr, unsigned char count);


//***************************************************************************
// Function Name : "block_read_RTC"
//					void block_read_RTC (volatile unsigned char *array_ptr,
//					unsigned char strt_addr, unsigned char count)
// Target MCU		: AVR128DB48 @ 4MHz
// Author			: Akm Islam
// DESCRIPTION
// This function reads a block of data from the DS1306 and transfers it to an
// array. strt_addr is the starting address in the DS1306. count is the number
// of data bytes to be transferred and array_ptr is the address of the
// destination array.
//**************************************************************************void block_read_RTC(volatile unsigned char *array_ptr, unsigned char strt_addr, unsigned char count);


//***************************************************************************
// Function Name : "block_write_read_RTC_test"
//					void block_write_read_RTC_test (void)
// Target MCU		: AVR128DB48 @ 4MHz
// Author			: Akm Islam
// DESCRIPTION
// This function uses the burst functions to read and write to the DS1306
// starting from a base address. Can be used to write and read to the Clock
// registers as well as the NV RAM.
//**************************************************************************
void block_write_read_RTC_test(void);


//***************************************************************************
// Function Name : "configure_DS1306"
//					void configure_DS1306 (void)
// Target MCU		: AVR128DB48 @ 4MHz
// Author			: Akm Islam
// DESCRIPTION
// This function configures the DS1306 for RTC use and alarm interrupts.
//**************************************************************************
void configure_DS1306(void);


#endif /* DS1306_RTC_DRIVERS_H_ */