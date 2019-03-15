/** \file

$Id: board.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "boarddiv.c"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "board.h"

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
const char l_board_PkgId[] = "board";

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void board_Init( void )
{
    boarddiv_Init();
}

#if BOARDDIV_LED_NUM > 0

void board_LedSetup( void )
{
    for( int i = 0; i < BOARDDIV_LED_NUM; i++ )
    {
        gpio_ConfigPin( &s_led[i] );
    }
}

void board_LedSet( board_LedIndicator_t x, bool s )
{
    gpio_SetPin( &s_led[x], s );
}

void board_LedToggle( board_LedIndicator_t x )
{
    gpio_TogglePin( &s_led[x] );
}

#endif


#if BOARDDIV_SPI_NUM > 0

void board_SpiSetup( board_Spi_t i )
{
    gpio_ConfigPin( &s_spi[i].sck );
    gpio_ConfigPin( &s_spi[i].miso );
    gpio_ConfigPin( &s_spi[i].mosi );
    gpio_ConfigPin( &s_spi[i].nss );  
    
#if defined( HAL_STM32F1 )
    if ( s_spi[i].remap )
    {
        gpio_Remap( &s_spi[i].sck,  s_spi[i].remap );
        gpio_Remap( &s_spi[i].miso, s_spi[i].remap );
        gpio_Remap( &s_spi[i].mosi, s_spi[i].remap );
        gpio_Remap( &s_spi[i].nss,  s_spi[i].remap );
    }
#endif
}

void board_SpiSlaveSelectSet( board_Spi_t i, bool s )
{ 
#if defined( HAL_STM32F4 )
    // NSS pin control only when Software Control selected
    // (nss control by Alternate hardware disabled)
    if ( s_spi[i].hwnss == false )
    {
        gpio_SetPin( &s_spi[i].nss, s );
    }
#endif

#if defined( HAL_STM32L ) || defined(HAL_STM32F4)
    gpio_SetPin( &s_spi[i].nss, s );
#endif
}

#if defined( HAL_STM32F4 )
SPI_TypeDef* board_SpiGetPeripheral( board_Spi_t i )
{
    return s_spi[i].peripheral;
}
#endif

#endif

const board_I2cInfo_t *board_I2cGetConfig( board_I2c_t busId )
{
    return (board_I2cInfo_t *)&s_i2c[busId];
}

/* End fo this file */