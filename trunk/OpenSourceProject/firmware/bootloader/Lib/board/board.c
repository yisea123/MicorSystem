/**
  ******************************************************************************
  *                     (c) Copyright 2018, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    board.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
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
    TM_Delay_ms(5);
    CTR_1_485_DIR_DISABLE;  
}

void Board_LedBlink( void )
{
    static bool ledRunFlag = false;

    ledRunFlag = !ledRunFlag;
    LED_SystemRun( ledRunFlag);
}

/* End of this file */