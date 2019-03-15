/** \file

$Id: boarddiv.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

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
#include "gpio.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "boarddiv.h"
#include "board.h"
#include "uart_local.h"

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/

static void boarddiv_Init(void);

/*!
 * @brief Definition of the LEDs
 */
static const gpio_Pin_t s_led[BOARDDIV_LED_NUM] =
{
  // LED -1
  {
    GPIOI,
    GPIO_PIN_10,
    {GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},
    false
  },
  
  // LED -2
  {
    GPIOF,
    GPIO_PIN_7,
    {GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},
    false
  },
  
  // LED -3
  {
    GPIOF,
    GPIO_PIN_8,
    {GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},
    false
  },
  
  // LED -4
  {
    GPIOC,
    GPIO_PIN_2,
    {GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, GPIO_SPEED_FREQ_LOW, 0},
    false
  }  
};

/*!
 * @brief Definition of the COM ports
 */
static const board_Usart_t s_com[BOARDDIV_COMPORT_NUM] =
{
  
  //com 1,  console
  {
     &g_usart_USART1,
    // Rx = PA10
    {
      GPIOA,
      GPIO_PIN_10,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART1
      },
      true
    },
    // Tx = PA9
    {
      GPIOA,
      GPIO_PIN_9,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART1
      },
      true
    },
    // Work with USART 1
    0
  },
  
  // com 2
  {
    &g_usart_USART2,
    // Rx = PA3
    {
      GPIOA,
      GPIO_PIN_3,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2
      },
      true
    },
    // Tx = PA2
    {
      GPIOA,
      GPIO_PIN_2,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART2
      },
      true
    },
    // Work with USART 2
    1
  },
  
  //com 3
  {
    &g_usart_USART3,
    // Rx = PB11
    {
      GPIOB,
      GPIO_PIN_11,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART3
      },
      true
    },
    // Tx = PB10
    {
      GPIOB,
      GPIO_PIN_10,
      {
        GPIO_MODE_AF_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_VERY_HIGH, GPIO_AF7_USART3
      },
      true
    },
    // Work with USART 3
    2
  },
  
};

/*!
 * @brief Definition of the spi ports
 */
static const board_SpiInfo_t s_spi[BOARDDIV_SPI_NUM] =
{
  // SPI1
  {
    // SCK =  PA5
    {
      GPIOA,
      GPIO_PIN_5,
      {
        GPIO_MODE_AF_PP,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_HIGH,
        GPIO_AF5_SPI1
      },
      true
    },

    // MISO = PA6
    {
      GPIOA,
      GPIO_PIN_6,
      {
        GPIO_MODE_AF_PP,
        GPIO_PULLDOWN,
        GPIO_SPEED_FREQ_HIGH,
        GPIO_AF5_SPI1
      },
      true
    },

    // MOSI = PA7
    {
      GPIOA,
      GPIO_PIN_7,
      {
        GPIO_MODE_AF_PP,
        GPIO_PULLDOWN,
        GPIO_SPEED_FREQ_HIGH,
        GPIO_AF5_SPI1
      },
      true
    },

    // NSS =  PA4 (Not Slave Select; polarity inverted -> false)
    {
      GPIOA,
      GPIO_PIN_4,
      {
        GPIO_MODE_OUTPUT_PP,
        GPIO_PULLUP,
        GPIO_SPEED_FREQ_HIGH,
        NULL
      },
      false
    },
    // With Alternate Function re-mapped (NO alternate function mapped)
    0,
    // Peripheral
    SPI1,
    // NSS by Alternate Function hardware: false = disabled (false = software controls pin state)
    false
  }
};

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/

/*!
 * @brief Additional initialization for the Boa reference board
 *
 * Apart from the generic setup functions, the Boa reference board
 * does not need specific initialization.
 */
static void boarddiv_Init(void)
{
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();
  __HAL_RCC_DMA2_CLK_ENABLE();
}

/* End fo this file */