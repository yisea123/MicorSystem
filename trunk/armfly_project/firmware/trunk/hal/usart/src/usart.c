/** \file

$Id: usart.c 40486 2018-09-20 13:50:21Z tangmingfei2013@126.com $

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
#include "uart_local.h"
#include "usart.h"

const char l_usart_PkgId[] = "Usart";

#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define DMAx_CLK_ENABLE()                __HAL_RCC_DMA1_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART2

/* Definition for USARTx's DMA */
#define USARTx_TX_DMA_CHANNEL            DMA_CHANNEL_4
#define USARTx_TX_DMA_STREAM             DMA1_Stream6
#define USARTx_RX_DMA_CHANNEL            DMA_CHANNEL_4
#define USARTx_RX_DMA_STREAM             DMA1_Stream5

/* Definition for USARTx's NVIC */
#define USARTx_DMA_TX_IRQn               DMA1_Stream6_IRQn
#define USARTx_DMA_RX_IRQn               DMA1_Stream5_IRQn
#define USARTx_DMA_TX_IRQHandler         DMA1_Stream6_IRQHandler
#define USARTx_DMA_RX_IRQHandler         DMA1_Stream5_IRQHandler
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

void uart_Init()
{
   UART_HandleTypeDef UartHandle;
    /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART1 configured as follow:
    - Word Length = 8 Bits
    - Stop Bit = One Stop bit
    - Parity = None
    - BaudRate = 9600 baud
    - Hardware flow control disabled (RTS and CTS signals) */
    UartHandle.Instance          = USART2;

    UartHandle.Init.BaudRate     = 9600;
    UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits     = UART_STOPBITS_1;
    UartHandle.Init.Parity       = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode         = UART_MODE_TX_RX;
    UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
}

/**
  * @brief UART MSP Initialization 
  *        This function configures the hardware resources used in this example: 
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  *           - DMA configuration for transmission request by peripheral 
  *           - NVIC configuration for DMA interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;
  
  GPIO_InitTypeDef  GPIO_InitStruct;
  
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* Enable GPIO TX/RX clock */
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();
  /* Enable USART2 clock */
  USARTx_CLK_ENABLE(); 
  /* Enable DMA1 clock */
  DMAx_CLK_ENABLE();   
  
  /*##-2- Configure peripheral GPIO ##########################################*/  
  /* UART TX GPIO pin configuration  */
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;
  
  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);
    
  /* UART RX GPIO pin configuration  */
  GPIO_InitStruct.Pin = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;
    
  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
    
  /*##-3- Configure the DMA streams ##########################################*/
  /* Configure the DMA handler for Transmission process */
  hdma_tx.Instance                 = USARTx_TX_DMA_STREAM;
  
  hdma_tx.Init.Channel             = USARTx_TX_DMA_CHANNEL;
  hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_tx.Init.Mode                = DMA_NORMAL;
  hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;
  hdma_tx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_tx.Init.MemBurst            = DMA_MBURST_INC4;
  hdma_tx.Init.PeriphBurst         = DMA_PBURST_INC4;
  
  HAL_DMA_Init(&hdma_tx);   
  
  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(huart, hdmatx, hdma_tx);
    
  /* Configure the DMA handler for Transmission process */
  hdma_rx.Instance                 = USARTx_RX_DMA_STREAM;
  
  hdma_rx.Init.Channel             = USARTx_RX_DMA_CHANNEL;
  hdma_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_rx.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_rx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
  hdma_rx.Init.Mode                = DMA_NORMAL;
  hdma_rx.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
  hdma_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_rx.Init.MemBurst            = DMA_MBURST_INC4;
  hdma_rx.Init.PeriphBurst         = DMA_PBURST_INC4; 

  HAL_DMA_Init(&hdma_rx);
    
  /* Associate the initialized DMA handle to the the UART handle */
  __HAL_LINKDMA(huart, hdmarx, hdma_rx);
    
  /*##-4- Configure the NVIC for DMA #########################################*/
  /* NVIC configuration for DMA transfer complete interrupt (USARTx_TX) */
  HAL_NVIC_SetPriority(USARTx_DMA_TX_IRQn, 0, 1);
  HAL_NVIC_EnableIRQ(USARTx_DMA_TX_IRQn);
    
  /* NVIC configuration for DMA transfer complete interrupt (USARTx_RX) */
  HAL_NVIC_SetPriority(USARTx_DMA_RX_IRQn, 0, 0);   
  HAL_NVIC_EnableIRQ(USARTx_DMA_RX_IRQn);
  
  /* NVIC configuration for USART TC interrupt */
  HAL_NVIC_SetPriority(USARTx_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USARTx_IRQn);
}

/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO, DMA and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  
  static DMA_HandleTypeDef hdma_tx;
  static DMA_HandleTypeDef hdma_rx;

  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
   
  /*##-3- Disable the DMA Streams ############################################*/
  /* De-Initialize the DMA Stream associate to transmission process */
  HAL_DMA_DeInit(&hdma_tx); 
  /* De-Initialize the DMA Stream associate to reception process */
  HAL_DMA_DeInit(&hdma_rx);
  
  /*##-4- Disable the NVIC for DMA ###########################################*/
  HAL_NVIC_DisableIRQ(USARTx_DMA_TX_IRQn);
  HAL_NVIC_DisableIRQ(USARTx_DMA_RX_IRQn);
}

/* End of this file */