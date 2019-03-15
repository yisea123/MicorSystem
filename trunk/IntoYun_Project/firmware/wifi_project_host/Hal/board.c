/** \file

$Id: board.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "board.h"

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "Includes.h"
#include "intoyun_hal.h"

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void Board_BlueTooth_Rest( void );

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void Board_Init( void )
{
    PERI_3V3_CTRL_PortConfig();
    BLUETOOTH_CTRL_PortConfig();
    WIFI_SETMODE_PortConfig();
    HW_LED_PortConfig();
    WIFI_REST_PortConfig();    
    CTR_1_485_DIR_PortConfig();
    CTR_2_485_DIR_PortConfig();
    
    PERI_3V3_CTRL_POWER_ON;
    
    Board_BlueTooth_Rest();
}

void Board_WifiEnterIntoBoot( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;	
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);     
   
    WIFI_SETMODE_LOW; 
    HAL_Delay( 1000 );
    WIFI_SETMODE_HIGH;
    HAL_Delay( 500 );
}

void HAL_485WriteSerial_Port1( uint8_t* buf, uint8_t len )
{
    CTR_1_485_DIR_ENABLE;
    UART1_Put( buf, len );
    HAL_Delay( 2 );
    CTR_1_485_DIR_DISABLE;
}

void HAL_485WriteSerial_Port2( uint8_t* buf, uint8_t len )
{
    CTR_2_485_DIR_ENABLE;
    UART2_Put( buf, len );
    HAL_Delay( 2 );
    CTR_2_485_DIR_DISABLE;   
}

static void Board_BlueTooth_Rest( void )
{
    BLUETOOTH_RST_CTRL_LOW;
    HAL_Delay( 500 );
    BLUETOOTH_RST_CTRL_HIGH;
    HAL_Delay( 500 );
}

/* End of this file */
