/** \file

$Id: i2c_stm32f4.c 40486 2018-09-26 6:59:21Z tangmingfei2013@126.com $

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
#include "i2c.h"

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#include "board.h"

#define ADAPTOR_TIMEOUT_US                200  ///200us
const char l_i2c_PkgId[] = "I2c";
DMA_HandleTypeDef hdma_i2c3_rx;

void i2c_InitPort(  const board_I2cInfo_t *const pBrdStruct,
                    bool useDma,
                    i2c_t *pi2c_t)
{
    I2C_HandleTypeDef *phi2c;
    
    phi2c = &pi2c_t->I2CHandle;
    
    pi2c_t->usesDma = useDma;
    pi2c_t->pBrdStruct = (board_I2cInfo_t*)pBrdStruct;
    
    phi2c->Instance = pBrdStruct->Instance;    
    phi2c->Init.ClockSpeed = 400000;
    phi2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
    phi2c->Init.OwnAddress1 = 0;
    phi2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    phi2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    phi2c->Init.OwnAddress2 = 0;
    phi2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    phi2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    
    phi2c->pUserData = (void *)pBrdStruct;
    
    if (HAL_I2C_Init( phi2c ) != HAL_OK)
    {
       assert_failed(__FILE__, __LINE__);
    } 
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    const board_I2cInfo_t *pBrdStruct = NULL;

    pBrdStruct = (board_I2cInfo_t*)hi2c->pUserData;
    if(hi2c->Instance==I2C1)
    {
          /* Peripheral clock enable */
          __HAL_RCC_I2C1_CLK_ENABLE();
    }
    else if(hi2c->Instance==I2C2)
    {
          /* Peripheral clock enable */
          __HAL_RCC_I2C2_CLK_ENABLE();
    }
    else if(hi2c->Instance==I2C3)
    {
          /* Peripheral clock enable */
          __HAL_RCC_I2C3_CLK_ENABLE();

          /* I2C3 DMA Init */
          /* I2C3_RX Init */
          hdma_i2c3_rx.Instance = DMA1_Stream2;
          hdma_i2c3_rx.Init.Channel = DMA_CHANNEL_3;
          hdma_i2c3_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
          hdma_i2c3_rx.Init.PeriphInc = DMA_PINC_DISABLE;
          hdma_i2c3_rx.Init.MemInc = DMA_MINC_ENABLE;
          hdma_i2c3_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
          hdma_i2c3_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
          hdma_i2c3_rx.Init.Mode = DMA_NORMAL;
          hdma_i2c3_rx.Init.Priority = DMA_PRIORITY_LOW;
          hdma_i2c3_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
          
          if (HAL_DMA_Init(&hdma_i2c3_rx) != HAL_OK)
          {
              assert_failed(__FILE__, __LINE__);
          }   
          __HAL_LINKDMA(hi2c,hdmarx,hdma_i2c3_rx);
          
          /* DMA controller clock enable */
          __HAL_RCC_DMA1_CLK_ENABLE();

          /* DMA interrupt init */
          /* DMA1_Stream2_IRQn interrupt configuration */
          HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 5, 0);
          HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

          /* DMA1_Stream3_IRQn interrupt configuration */
          HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, 5, 0);
          HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);          
    }

    /*##-3- Configure peripheral GPIO
    ##########################################*/
    /*##- Disable peripherals and GPIO Clocks
    #################################*/
    /* Configure I2C SCL as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->scl.pBlock, pBrdStruct->scl.pin);
    /* Configure I2C SDA as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->sda.pBlock, pBrdStruct->sda.pin);

    /* I2C SCL GPIO pin configuration  */
    GPIO_InitStruct.Pin       = pBrdStruct->scl.pin;
    GPIO_InitStruct.Mode      = pBrdStruct->scl.opMode.Mode;
    GPIO_InitStruct.Pull      = pBrdStruct->scl.opMode.Pull;
    GPIO_InitStruct.Speed     = pBrdStruct->scl.opMode.Speed;
    GPIO_InitStruct.Alternate = pBrdStruct->scl.opMode.Alternate;
    HAL_GPIO_Init(pBrdStruct->scl.pBlock, &GPIO_InitStruct);

    /* I2C SDA GPIO pin configuration  */
    GPIO_InitStruct.Pin       = pBrdStruct->sda.pin;
    GPIO_InitStruct.Alternate = pBrdStruct->sda.opMode.Alternate;
    HAL_GPIO_Init(pBrdStruct->sda.pBlock, &GPIO_InitStruct);  
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
    const board_I2cInfo_t *pBrdStruct = NULL;

    pBrdStruct = (board_I2cInfo_t*)hi2c->pUserData;
    if(hi2c->Instance==I2C1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_I2C1_CLK_DISABLE();
    }
    else if(hi2c->Instance==I2C2)
    {
        /* Peripheral clock disable */
        __HAL_RCC_I2C2_CLK_DISABLE();
    }
    else if(hi2c->Instance==I2C3)
    {
        /* Peripheral clock disable */
        __HAL_RCC_I2C3_CLK_DISABLE();

        /* I2C3 DMA DeInit */
        HAL_DMA_DeInit(hi2c->hdmarx);
    }

    /*##-2- Disable peripherals and GPIO Clocks
    #################################*/
    /* Configure I2C SCL as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->scl.pBlock, pBrdStruct->scl.pin);
    /* Configure I2C SDA as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->sda.pBlock, pBrdStruct->sda.pin);  
}

/**
* @brief This function handles DMA1 stream2 global interrupt.
*/
void DMA1_Stream2_IRQHandler(void)
{
  HAL_DMA_IRQHandler(&hdma_i2c3_rx);
}

I2C_StatusDef i2c_master_sync_read_with_index
(
  i2c_t *pI2C,
  uint8_t devAddr,
  uint16_t regAddr,
  uint8_t  regAddrLen,
  uint8_t *pRdBuf,
  uint16_t bufRdLen
)
{
    if (HAL_I2C_Mem_Read(&(pI2C->I2CHandle), devAddr, regAddr,
                         regAddrLen,
                         pRdBuf, bufRdLen, ADAPTOR_TIMEOUT_US) != HAL_OK)
    {
        return I2C_ERROR;
    }
    
    return I2C_OK;
}

I2C_StatusDef i2c_master_sync_write_with_index
(
  i2c_t *pI2C,
  uint8_t devAddr,
  uint16_t regAddr,
  uint8_t  regAddrLen,
  uint8_t *pWrBuf,
  uint16_t bufWrLen
)
{
    if (HAL_I2C_Mem_Write(&(pI2C->I2CHandle), (uint16_t)devAddr, regAddr,
                           (uint16_t)regAddrLen,
                            pWrBuf, bufWrLen, ADAPTOR_TIMEOUT_US) != HAL_OK)
    {
        return I2C_ERROR;
    }

    return I2C_OK;
}

/* End of this file */
