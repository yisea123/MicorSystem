#ifndef __BOARD_H
#define __BOARD_H


#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/*******************************************************************************
               led port 
*******************************************************************************/
#define LEDn                             ((uint8_t)2)

#define LED_Y_GPIO_PORT                   GPIOC
#define LED_Y_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_Y_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_R_GPIO_PORT                   GPIOC
#define LED_R_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define LED_R_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

#define LED_Y_PIN                         GPIO_PIN_1
#define LED_R_PIN                         GPIO_PIN_2

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LED_Y_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 1) LED_R_GPIO_CLK_ENABLE(); \
                                            }while(0)

#define LEDx_GPIO_CLK_DISABLE(__INDEX__)  do{if((__INDEX__) == 0) LED_Y_GPIO_CLK_DISABLE(); else \
                                             if((__INDEX__) == 1) LED_R_GPIO_CLK_DISABLE(); \
                                             }while(0)
                                               
/*******************************************************************************
               Debug port 
*******************************************************************************/
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
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

/* Definition for USARTx's NVIC */
#define USARTx_IRQn                      USART2_IRQn
#define USARTx_IRQHandler                USART2_IRQHandler

                                               
extern DMA_HandleTypeDef hdma_spi2_rx;
extern I2S_HandleTypeDef hi2s2;
extern UART_HandleTypeDef Uart2Handle;
/* Exported functions ------------------------------------------------------- */                                               
void vAsb_InitBoard( void );
void log_Printf( uint8_t *buff, uint16_t length );
void vAsb_BoardTest( void );
void Error_Handler(void);


#endif /* __BOARD_H */                                               
                                               