/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "stm32f4xx_hal.h"
#include "stm32f_Flash.h"
#include "board.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_DEBUG_MESSAGE_LENGTH        512

#if !defined(arraySize)
#   define arraySize(a)            (sizeof((a))/sizeof((a[0])))
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static IWDG_HandleTypeDef hiwdg;

/* Extern variables ---------------------------------------------------------*/
DMA_HandleTypeDef hdma_spi2_rx;
I2S_HandleTypeDef hi2s2;
UART_HandleTypeDef Uart2Handle;

/* Private function prototypes -----------------------------------------------*/
static void vLed_InitPort( void );
static void MX_USART2_UART_Init( void );
static void MX_IWDG_Init(void);
static void MX_I2S2_Init(void);

/* Private functions ---------------------------------------------------------*/
static void vLed_InitPort( void )
{
  static GPIO_InitTypeDef  GPIO_InitStruct;

  /* -1- Enable GPIO Clock (to be able to program the configuration registers) */
  LED_Y_GPIO_CLK_ENABLE();
  LED_R_GPIO_CLK_ENABLE();

  /* -2- Configure IO in output push-pull mode to drive external LEDs */
  GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

  GPIO_InitStruct.Pin = LED_Y_PIN;
  HAL_GPIO_Init(LED_Y_GPIO_PORT, &GPIO_InitStruct);
  GPIO_InitStruct.Pin = LED_R_PIN;
  HAL_GPIO_Init(LED_R_GPIO_PORT, &GPIO_InitStruct);
}

/* uart 2 init function */
static void MX_USART2_UART_Init( void )
{
  Uart2Handle.Instance          = USARTx;
  
  Uart2Handle.Init.BaudRate     = 115200;
  Uart2Handle.Init.WordLength   = UART_WORDLENGTH_8B;
  Uart2Handle.Init.StopBits     = UART_STOPBITS_1;
  Uart2Handle.Init.Parity       = UART_PARITY_NONE;
  Uart2Handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  Uart2Handle.Init.Mode         = UART_MODE_TX_RX;
  Uart2Handle.Init.OverSampling = UART_OVERSAMPLING_16;
    
  if(HAL_UART_Init(&Uart2Handle) != HAL_OK)
  {
    Error_Handler();
  }    
}

/* IWDG init function */
static void MX_IWDG_Init(void)
{
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
}

/* I2S2 init function */
static void MX_I2S2_Init(void)
{

  hi2s2.Instance = SPI2;
  hi2s2.Init.Mode = I2S_MODE_MASTER_RX;
  hi2s2.Init.Standard = I2S_STANDARD_LSB;
  hi2s2.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s2.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s2.Init.AudioFreq = 64000;
  hi2s2.Init.CPOL = I2S_CPOL_LOW;
  hi2s2.Init.ClockSource = I2S_CLOCK_PLL;
  hi2s2.Init.FullDuplexMode = I2S_FULLDUPLEXMODE_DISABLE;
  if (HAL_I2S_Init(&hi2s2) != HAL_OK)
  {
    Error_Handler();
  }

}

/** 
  * Enable DMA controller clock
  * Configure DMA for memory to memory transfers
  *   hdma_memtomem_dma2_stream0
  */
static void MX_DMA_Init(void) 
{
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

void Error_Handler(void)
{
  while(1)
  {
    
  }
}

/* Stm32 internal flash test */
static void test_stm32_internal_flash( void )
{
    #define max_len 512
  
    uint8_t wbuff[max_len];
    uint8_t rbuff[max_len];
    uint32_t address = 1*256 + ADDR_FLASH_SECTOR_8;

    for( uint32_t i = 0; i < max_len; i++  )
    {
        wbuff[i] = i;
    }
    
    stm32fdisk_Erase(address, max_len);
    stm32fdisk_Read(address,  rbuff, max_len  );
    stm32fdisk_Write(address,  wbuff, max_len );
    stm32fdisk_Read( address,  rbuff,  max_len  );    
    
    for( uint32_t i = 0; i < max_len; i++  )
    {
        if(wbuff[i] != rbuff[i])
        {
            log_Printf(" internal flash verify error \r\n", sizeof(" internal flash verify error \r\n"));
            return;
        }
    }
}

/* Export functions ---------------------------------------------------------*/
void vAsb_InitBoard( void )
{
   vLed_InitPort();
   MX_USART2_UART_Init();
  // MX_IWDG_Init();
   stm32fdisk_Init();
   MX_DMA_Init();
   MX_I2S2_Init();
}
   
void vAsb_BoardTest( void )
{
   test_stm32_internal_flash();
    while(1)
    {
        HAL_GPIO_TogglePin(LED_Y_GPIO_PORT, LED_Y_PIN);
        /* Insert delay 1000 ms */
        HAL_Delay(1000);
        HAL_GPIO_TogglePin(LED_R_GPIO_PORT, LED_R_PIN);
        /* Insert delay 1000 ms */
        HAL_Delay(1000);
        log_Printf("asb board driver test \r\n", sizeof("asb board driver test \r\n"));
    }
}

void log_Printf( uint8_t *buff, uint16_t length )
{
  if(HAL_UART_Transmit(&Uart2Handle, (uint8_t *)buff, length, 5000) != HAL_OK)
  {
    Error_Handler();    
  }
}

void _log_print(const char *fmt, ...)
{
    char _buffer[MAX_DEBUG_MESSAGE_LENGTH];
    va_list args;
    int trunc;

    va_start(args, fmt);
    trunc = vsnprintf(_buffer, arraySize(_buffer), fmt, args);
    log_Printf((uint8_t*)_buffer,trunc);
    va_end(args);
}

/* End of this file */