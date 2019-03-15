/** \file

$Id: usart.c 40486 2018-09-20 05:50:21Z tangmingfei2013@126.com $

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

/* Private function prototypes -----------------------------------------------*/
static void theHandler(uint8_t index);

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
const char l_usart_PkgId[] = "Usart";

/*!
 * @brief An installed interrupt handler for each USART.
 */
static usart_t *s_pUsart[] =
{
#ifdef USART1
  NULL
#endif
    
#ifdef USART2
  ,NULL
#endif
    
#ifdef USART3
  ,NULL
#endif
};

#ifdef USART1
static UART_HandleTypeDef huart1 =
{
  .Instance = USART1,
};

const usart_Peripheral_t g_usart_USART1 =
{
  &huart1,
  DMA2_Stream7,
  DMA_CHANNEL_4,
  USART1_IRQn,
  DMA2_Stream7_IRQn
};
#endif

#ifdef USART2
static UART_HandleTypeDef huart2 =
{
  .Instance = USART2,
};

const usart_Peripheral_t g_usart_USART2 =
{
  &huart2,
  DMA1_Stream6,
  DMA_CHANNEL_4,
  USART2_IRQn,
  DMA1_Stream6_IRQn
};
#endif

#ifdef USART3
static UART_HandleTypeDef huart3 =
{
  .Instance = USART3,
};

const usart_Peripheral_t g_usart_USART3 =
{
  &huart3,
  DMA1_Stream4,
  DMA_CHANNEL_7,
  USART3_IRQn,
  DMA1_Stream4_IRQn
};
#endif

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/

void uart_Init( uint32_t BaudRate,
                usart_t *pUsart,
                const board_Usart_t *const pBrdStruct)
{
    const int usartIndex = pBrdStruct->usartIndex;
    UART_HandleTypeDef *pUsartHandle = pBrdStruct->pPeripheral->peripheral;  
    
    /* Install the interrupt handler callback */
    s_pUsart[ usartIndex ] = pUsart; 
    pUsart->pBrdStruct = pBrdStruct;   
   
    /*##-1- Configure the UART peripheral ######################################*/
    /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
    /* UART1 configured as follow:
        - Word Length = 8 Bits
        - Stop Bit = One Stop bit
        - Parity = None
        - BaudRate = 9600 baud
        - Hardware flow control disabled (RTS and CTS signals) */   
    pUsartHandle->pUserData         = (void *)pUsart;
    pUsartHandle->Init.BaudRate     = BaudRate;
    pUsartHandle->Init.WordLength   = UART_WORDLENGTH_8B;
    pUsartHandle->Init.StopBits     = UART_STOPBITS_1;
    pUsartHandle->Init.Parity       = UART_PARITY_NONE;
    pUsartHandle->Init.HwFlowCtl    = UART_HWCONTROL_NONE;
    pUsartHandle->Init.Mode         = UART_MODE_TX_RX;
    pUsartHandle->Init.OverSampling = UART_OVERSAMPLING_16; 
    
    if (HAL_UART_DeInit(pUsartHandle) != HAL_OK)
    {
        assert_failed(__FILE__, __LINE__);
    }
    
    if (HAL_UART_Init(pUsartHandle) != HAL_OK)
    {
        assert_failed(__FILE__, __LINE__);
    }      
    
    if (HAL_UART_Receive_IT( pUsartHandle, pUsart->pRxBuf,USART_RX_BUF_SIZE) != HAL_OK)
    {
        assert_failed(__FILE__, __LINE__);
    }
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;
    const board_Usart_t *pBrdStruct = NULL;
    usart_t *pUsart = (usart_t *)(huart->pUserData); 
    
    /*##-1- Enable peripherals and GPIO Clocks #################################*/  
    /* Enable USARTx clock */
#ifdef USART1
    if ((uint32_t)(huart->Instance) == (uint32_t)USART1)
    {
        /* USER CODE BEGIN USART1_MspInit 0 */

        /* USER CODE END USART1_MspInit 0 */
        /* USART1 clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
    }
    else
#endif  
  
#ifdef USART2
    if ((uint32_t)(huart->Instance) == (uint32_t)USART2)
    {
        /* USER CODE BEGIN USART2_MspInit 0 */

        /* USER CODE END USART2_MspInit 0 */
        /* USART2 clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();
    }
    else
#endif

#ifdef USART3
    if ((uint32_t)(huart->Instance) == (uint32_t)USART3)
    {
        /* USER CODE BEGIN USART3_MspInit 0 */

        /* USER CODE END USART3_MspInit 0 */
        /* USART5 clock enable */
        __HAL_RCC_USART3_CLK_ENABLE();
    }
    else
#endif
    {
        assert_failed(__FILE__, __LINE__);
    }     
    
    /* Enable GPIO TX/RX clock */
    /* Enable USART clock */
    pBrdStruct = pUsart->pBrdStruct;

    /*##-2- Configure peripheral GPIO ##########################################*/  
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = (uint32_t)pBrdStruct->tx.pin;
    GPIO_InitStruct.Mode      = pBrdStruct->tx.opMode.Mode;
    GPIO_InitStruct.Pull      = pBrdStruct->tx.opMode.Pull;
    GPIO_InitStruct.Speed     = pBrdStruct->tx.opMode.Speed;
    GPIO_InitStruct.Alternate = pBrdStruct->tx.opMode.Alternate;
    HAL_GPIO_Init(pBrdStruct->tx.pBlock, &GPIO_InitStruct);

    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin =(uint32_t)pBrdStruct->rx.pin;
    GPIO_InitStruct.Alternate = pBrdStruct->rx.opMode.Alternate;
    HAL_GPIO_Init(pBrdStruct->rx.pBlock, &GPIO_InitStruct);

    /*##-3- Configure the NVIC for UART ########################################*/
    /* NVIC for USART */
    HAL_NVIC_SetPriority(pBrdStruct->pPeripheral->usartIrqId, 0, 1);
    HAL_NVIC_EnableIRQ(pBrdStruct->pPeripheral->usartIrqId);
}


/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    const board_Usart_t *pBrdStruct = NULL;
    usart_t *pUsart = (usart_t *)(huart->pUserData);

   /* Disable USARTx clock */
#ifdef USART1
    if ((uint32_t)(huart->Instance) == (uint32_t)USART1)
    {
        /* USER CODE BEGIN USART1_MspInit 0 */

        /* USER CODE END USART1_MspInit 0 */
        /* USART1 clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();
    }
    else
#endif

#ifdef USART2
    if ((uint32_t)(huart->Instance) == (uint32_t)USART2)
    {
        /* USER CODE BEGIN USART2_MspInit 0 */

        /* USER CODE END USART2_MspInit 0 */
        /* USART2 clock disable */
        __HAL_RCC_USART2_CLK_DISABLE();
    }
    else
#endif

#ifdef USART3
    if ((uint32_t)(huart->Instance) == (uint32_t)USART3)
    {
        /* USER CODE BEGIN USART3_MspInit 0 */

        /* USER CODE END USART3_MspInit 0 */
        /* USART3 clock disable */
        __HAL_RCC_USART3_CLK_DISABLE();
    }
    else
#endif
    {
        assert_failed(__FILE__, __LINE__);
    }

    pBrdStruct = pUsart->pBrdStruct;
    /*##-2- Disable peripherals and GPIO Clocks
    #################################*/
    /* Configure USARTx Tx as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->tx.pBlock, (uint32_t)pBrdStruct->tx.pin);
    /* Configure USARTx Rx as alternate function  */
    HAL_GPIO_DeInit(pBrdStruct->rx.pBlock, (uint32_t)pBrdStruct->rx.pin);

    /*##-3- Disable the DMA */
    HAL_NVIC_DisableIRQ(pBrdStruct->pPeripheral->usartIrqId);
}

/*!
 * @brief Interrupt handler for USART 1
 */
#ifdef USART1
void USART1_IRQHandler(void)
{
    theHandler(0);
}
#endif

/*!
 * @brief Interrupt handler for USART 2
 */
#ifdef USART2
void USART2_IRQHandler(void)
{
    theHandler(1);
}
#endif

/*!
 * @brief Interrupt handler for USART 3 (if existing)
 */
#ifdef USART3
void USART3_IRQHandler(void)
{
    theHandler(2);
}
#endif

void uart_SendBuffer(usart_t *pUsart, uint8_t *aTxBuffer, uint16_t nBytes )
{
    UART_HandleTypeDef *uartHandle = NULL;
    uartHandle = pUsart->pBrdStruct->pPeripheral->peripheral;

    if (HAL_UART_Transmit_IT(uartHandle, aTxBuffer, (uint16_t)nBytes) != HAL_OK)
    {
    // Transmit error
    // assert_failed(__FILE__, __LINE__);
    }    
}

void usart_SendByte(usart_t *pUsart, uint8_t byte)
{
    UART_HandleTypeDef *uartHandle = NULL;
    uartHandle = pUsart->pBrdStruct->pPeripheral->peripheral;

    HAL_UART_Transmit(uartHandle, (uint8_t *)&byte, 1, 0xFFFF);
    pUsart->txState = usart_TxState_Running;
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of DMA Rx transfer
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
    usart_t *pUsart = (usart_t *)(UartHandle->pUserData);

    if (pUsart != NULL)
    {
        if (HAL_UART_Receive_IT(UartHandle, pUsart->pRxBuf,
                                USART_RX_BUF_SIZE) != HAL_OK)
        {
          // Receiving error
        }
    }
}

static void theHandler(uint8_t index)
{
    usart_t *pUsart = s_pUsart[index];

    if (pUsart != NULL &&
        pUsart->pBrdStruct != NULL &&
        pUsart->pBrdStruct->pPeripheral != NULL &&
        pUsart->pBrdStruct->pPeripheral->peripheral != NULL)
    {
        HAL_UART_IRQHandler(pUsart->pBrdStruct->pPeripheral->peripheral);
    }
}

/* End of this file */
