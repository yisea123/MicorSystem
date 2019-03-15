/**************************************************** **************************
* File Name          : Board.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/02/25
* Description        : for wifi project slave
********************************************************************************
*/
#include "Includes.h"

void Board_Init( void )
{
    HW_LED_PortConfig();
    CTR_1_485_DIR_PortConfig();
    PERI_3V3_CTRL_PortConfig();
    HW_LED_PortConfig();
    
    PERI_3V3_CTRL_POWER_ON;
}


void HAL_485WriteSerial( INT8U* pu8_buf, INT8U u8_len )
{
    CTR_1_485_DIR_ENABLE;
    UART1_Put( pu8_buf, u8_len );
    CTR_1_485_DIR_DISABLE;
    
}

void Board_LedBlink( void )
{
    static bool ledRunFlag = FALSE;

    ledRunFlag = !ledRunFlag;
    LED_SystemRun( ledRunFlag);
}

/* End of this file */