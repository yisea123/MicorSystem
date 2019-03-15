/*******************************************************************************

 	 Error Reporting System

   (C) Copyright 2006, RAE Systems Inc. 	 All rights reserved

--------------------------------------------------------------------------------

     File name: ERR_sys.H
      Hardware: ARM7TDMI
     Reference:

--------------------------------------------------------------------------------

   == Important Note ==

   . ERR_Code is a 4-byte variable and has bit definition shown below
        b0~b7: error flags
       b8~b15: MCU error source
      b16~b31: app-defined error flags

--------------------------------------------------------------------------------

   Revision History

   == V1.00.00 ==
      Jun. 27, 2006 - copy from ERR_sys.c and expand ERR_Code to 4 bytes.

   == V1.00.01 ==
      07/13/06 - Wenpeng, review and VSS

   == V1.00.02 ==
      08/19/06 - Wenpeng, move MCU source to bit8~15

*******************************************************************************/


/************************Error source and flag definitions*********************/

#define ERROR_NONE        0x00000000

// Error flags - bit 16-19
#define ERR_READ        0x00020000
#define ERR_WRITE       0x00040000
#define ERR_TIMEOUT     0x00080000

// MCU error sources - bit 20-31
#define ERR_ADC10       0x00100000        // ADC
#define ERR_DAC         0x00200000        // DAC
#define ERR_FLASH       0x00400000        // Flash
#define ERR_I2C         0x00800000        // I2C
#define ERR_SPI         0x01000000        // SPI
#define ERR_UART        0x02000000        // UART
#define ERR_IAP         0x04000000        // IAP
#define ERR_WD          0x08000000        // Watchdog


#define ERR_SMM_BUFF1               1     // AT45DB buffer 1 error
#define ERR_SMM_BUFF2               2     // AT45DB buffer 2 error
#define ERR_SMM_TIMEOUT             3     // AT45DB get status timeout
#define ERR_SMM_ADDR                4     // Address is greater than total memory size
#define ERR_START                   5     // I2C Start fail
#define ERR_AT24_ADDRW              6     // AT24 device address write fail
#define ERR_AT24_ADDRR              7     // AT24 device address read fail
#define ERR_AT24_DATAWRITE          8     // AT24 data write error
#define ERR_AT24_DATAREAD           9     // AT24 data read error
#define ERR_DS1337_ADDRW            10    // DS1337 device address write fail
#define ERR_DS1337_ADDRR            11    // DS1337 device address read fail
#define ERR_DS1337_DATAWRITE        12    // DS1337 data write error
#define ERR_DS1337_DATAREAD         13    // DS1337 data read error
#define ERR_ZLG7290_ADDRW           14    // ZLG7290 device address write fail
#define ERR_ZLG7290_ADDRR           15    // ZLG7290 device address read fail
#define ERR_ZLG7290_DATAWRITE       16    // ZLG7290 data write error
#define ERR_ZLG7290_DATAREAD        17    // ZLG7290 data read error
#define ERR_M29W_MANUFACTURER       18    // M29W manufacturer code error
#define ERR_M29W_DEVICE             19    // M29W device code error
#define ERR_M29W_WRITE              20    // M29W write failed


/*******************************************************************************

   Function Prototypes

--------------------------------------------------------------------------------

   ERR_GetCode() will return the last error code recorded and clear error code.

*******************************************************************************/

INT32U ERR_GetCode( void );
INT32U ERR_PeekCode( void );
void ERR_SetCode( INT32U error );



