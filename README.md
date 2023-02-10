# Data-Logger
Embedded System project that collects ambient temperature as well as time to display on an LCD module. 
Features the use of ADC, SPI, and USART modules. 
When the system is connected to a Windows terminal emulator via the COM port, it features a FSM-driven user interface to change the time and store in the real-time clock IC.

The entire design is interrupt driven, for ADC calculations, SPI read and writes, and USART communication.

This design targets an AVR128DB48 microcontroller. It is an AVR microproccessor accompanied by many peripherals, such as the ones utilized in this project. All the programs are written in C.
