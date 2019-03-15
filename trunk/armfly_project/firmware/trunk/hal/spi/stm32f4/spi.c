/** \file

$Id: usart.c 40486 2018-09-21 13:40:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "spi.h"

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#include <string.h> /* memcpy() */
#include "board.h"

/******************************************************************************
* LOCAL MACROS AND CONSTANTS
******************************************************************************/
#define FLASH_DUMMY_BYTE            0xFF 

/******************************************************************************
* LOCAL TYPES
******************************************************************************/

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static SPI_HandleTypeDef hspi1;
static uint32_t SpixTimeout = 1000; /*<! Value of Timeout when SPI communication fails */
const char l_spi_PkgId[] = "spi";

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/

static void spi_stm32f_Error (void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&hspi1);
}

/**
  * @brief  SPI Write a byte to device
  * @param  DataIn: value to be written
  * @param  DataOut: read value
  * @param  DataLength: number of bytes to write
  * @retval None
  */
static void SPIx_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut, uint16_t DataLength)
{
    HAL_StatusTypeDef status = HAL_OK;

    status = HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) DataIn, DataOut, DataLength, SpixTimeout);
      
    /* Check the communication status */
    if(status != HAL_OK)
    {
      /* Execute user timeout callback */
      spi_stm32f_Error();
    }
}

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void spi_Impl_Init( void )
{
    __HAL_RCC_SPI1_CLK_ENABLE();

    board_SpiSetup( board_Spi_1 );
    /* SPI1 parameter configuration*/
    hspi1.Instance = board_SpiGetPeripheral( board_Spi_1 );
    hspi1.Init.Mode = SPI_MODE_MASTER;
    hspi1.Init.Direction = SPI_DIRECTION_2LINES;
    hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi1.Init.NSS = SPI_NSS_SOFT;
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi1.Init.CRCPolynomial = 10;

    HAL_SPI_Init(&hspi1);
}

uint8_t spif_Impl_SendByte( uint8_t Data )
{
    uint8_t tmp;
    /* Send the byte */
    SPIx_WriteReadData(&Data,&tmp,1);
    return tmp;
}

/* End fof this file */