/*
 * DOG_LCD.h
 *
 * Created: 4/14/2021 12:08:43 AM
 *  Author: Akm Islam
 */ 


#ifndef DOG_LCD_H_
#define DOG_LCD_H_

#define line_size 16

// Function Prototypes.

//***************************************************************************
//
// Function Name        : "lcd_spi_transmit_CMD"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function transmits commands to the LCD DOG. Uses
//						SPI with RS = 0.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void lcd_spi_transmit_CMD (unsigned char cmd);


//***************************************************************************
//
// Function Name        : "lcd_spi_transmit_DATA"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function transmits data to the LCD DOG. Uses
//						SPI with RS = 1.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void lcd_spi_transmit_DATA (unsigned char cmd);


//***************************************************************************
//
// Function Name        : "init_spi_lcd"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function initializes the SPI module to
//						communicate with the LCD DOG module. Uses mode 1,1.
//						SCK is set to 2MHz.
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//
//**************************************************************************
void init_spi_lcd (void);


//***************************************************************************
//
// Function Name        : "init_lcd_dog"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function initializes the LCD DOG module. It
//						sends commands to the MCU to initialize the LCD DOG
//						to our desire.
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : init_spi_lcd, lcd_spi_transmit_CMD
//
// Revision History     : Initial version
//
//**************************************************************************
void init_lcd_dog (void);


//***************************************************************************
//
// Function Name        : "update_lcd_dog"
// Date                 : 4/6/21
// Version              : 1.0
// Target MCU           : AVR128
// Target Hardware      ; AVR128DB48
// Author               : Akm Islam
// DESCRIPTION			This function updates the LCD module to display the
//						newest contents of the dsp_buffers.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : init_spi_lcd, lcd_spi_transmit_CMD,
//						  lcd_spi_transmit_DATA
//
// Revision History     : Initial version
//
//**************************************************************************
void update_lcd_dog (void);

// Global Variable Declarations.
char dsp_buff1[17];
char dsp_buff2[17];
char dsp_buff3[17];


#endif /* DOG_LCD_H_ */