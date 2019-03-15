/** \file

$Id: Init.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "Includes.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define LED_TIMER_NUM       1

#if 0  /* for external CLOCK */
static void Init_RCC_Configuration(void)
{
    SystemInit();
    ErrorStatus HSEStartUpStatus;  
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Wait till HSE is ready */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        /* Flash 2 wait state */
        FLASH_SetLatency(FLASH_Latency_2);

        /* HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1); 

        /* PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1); 

        /* PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);

        /* ADCCLK = PCLK2/4 */
        RCC_ADCCLKConfig(RCC_PCLK2_Div4); 

        /* PLLCLK = 8MHz * 7 = 56 MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_7);

        /* Enable PLL */ 
        RCC_PLLCmd(ENABLE);

        /* Wait till PLL is ready */
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        /* Wait till PLL is used as system clock source */
        while(RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }
    RCC_AHBPeriphClockCmd(  RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2,  ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|  	\
                            RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|          \
                            RCC_APB2Periph_GPIOE|RCC_APB2Periph_ADC1|    	\
                            RCC_APB2Periph_ADC3|RCC_APB2Periph_ADC2 |		\
                            RCC_APB2Periph_SPI1|RCC_APB2Periph_USART1|	        \
                            RCC_APB2Periph_AFIO, ENABLE );  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2|RCC_APB1Periph_I2C1|          \
                            RCC_APB1Periph_TIM3|RCC_APB1Periph_CAN1|            \
                            RCC_APB1Periph_UART4|RCC_APB1Periph_WWDG|           \
                            RCC_APB1Periph_USART3, ENABLE );           
}
#else  /* for internal CLOCK */
/*
* CLOCK TABLE:
* SYSCLK_FRE: 56000000
* HCLK_FRE:   56000000
* PCLK1_FRE:  28000000
* PCLK2_FRE： 28000000
* ADCCLK_FRE: 14000000
*/

static void Init_RCC_Configuration(void)
{
    /* RCC system reset(for debug purpose) */
    RCC_DeInit();
    RCC_HSICmd( ENABLE );
 
    /* Wait till HSI is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
    {
    }
    
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
  
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* ADCCLK = PCLK2/4 */
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
    
    /* PLLCLK = 4MHz * 14 = 56 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_14);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);
    
     /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }   

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }    
    
    RCC_AHBPeriphClockCmd(  RCC_AHBPeriph_DMA1|RCC_AHBPeriph_DMA2,  ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|       \
                            RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|       \
                            RCC_APB2Periph_GPIOE|RCC_APB2Periph_ADC1|        \
                            RCC_APB2Periph_ADC3|RCC_APB2Periph_ADC2 |        \
                            RCC_APB2Periph_SPI1|RCC_APB2Periph_USART1|       \
                            RCC_APB2Periph_AFIO, ENABLE );  
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2|RCC_APB1Periph_I2C1|       \
                            RCC_APB1Periph_TIM3|RCC_APB1Periph_CAN1|         \
                            RCC_APB1Periph_UART4|RCC_APB1Periph_WWDG|        \
                            RCC_APB1Periph_USART3|RCC_APB1Periph_UART5, ENABLE );
    
}
#endif

void Init_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
 
#if ( UART1_EN > 0U )  
     // Enable the USART1 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     
#endif    
    
#if ( UART2_EN > 0U )      
    // Enable the USART2 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if ( UART3_EN > 0U )
      // Enable the USART3 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if ( UART4_EN > 0U )
      // Enable the USART4 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if ( UART5_EN > 0U )
      // Enable the USART4 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif     
    
 
#if ( TIM2_EN > 0U )
    // Enable the TIM2 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if ( TIM3_EN > 0U )
    // Enable the TIM3 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif
    
#if ( TIM4_EN > 0U )      
    // Enable the TIM4 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if( WDG_EN > 0u  )
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);    
#endif     
    
}

static void Init_Stm32( void )
{
#if ( UART1_EN > 0U )
    UART_Init( st_Uart1,PORT_UART1, UART_BDR9600 );
    HAL_485WriteSerial_Port1("485 PORT-1 Init OK! \r\n",sizeof( "485 PORT-1 Init OK! \r\n" ));
#endif

#if ( UART2_EN > 0U )
    UART_Init( st_Uart2,PORT_UART2, UART_BDR9600);
    HAL_485WriteSerial_Port2("485 PORT-2 Init OK! \r\n",sizeof( "485 PORT-2 Init OK! \r\n" ));
#endif 

#if ( UART4_EN > 0U )
    UART_Init( st_Uart4,PORT_UART4, UART_BDR115200);
    UART4_Put("USART4 Init OK! \r\n",sizeof( "USART4 Init OK! \r\n" ));
#endif     

#if ( UART3_EN > 0U )
    UART_Init( st_Uart3,PORT_UART3, UART_BDR115200);
    UART3_Put("USART3 Init OK! \r\n",sizeof( "USART3 Init OK! \r\n" ));
#endif 
    
#if ( UART5_EN > 0U )
    UART_Init( st_Uart5,PORT_UART5, UART_BDR9600);
    UART5_Put("USART5 Init OK! \r\n",sizeof( "USART5 Init OK! \r\n" ));
#endif     
    
#if( WDG_EN > 0u  )
    WDG_Init();
#endif
     
    Init_NVIC_Configuration();
}

static void Init_Devices( void )
{
    Timer.timerRegister(LED_TIMER_NUM, 500, false, LedBlink);
    SPIx_Init( SPIX1 );
    W25QXX_Init();
}

void Init_System( void )
{    
    Init_RCC_Configuration();
   
    if (SysTick_Config(SystemFrequency / 1000))       /* Setup SysTick Timer for 1 msec interrupts  */
    { 
        /* Capture error */ 
        while (1);
    }
    
    Board_Init();
    Init_Stm32();
    
    Init_Devices();
    HAL_Delay( 1000 );
    Sys_InformationInit();
    
    vApps_BlueToothActionInit();
    vApps_DebugActionInit();
}

/* End fo this file  */
