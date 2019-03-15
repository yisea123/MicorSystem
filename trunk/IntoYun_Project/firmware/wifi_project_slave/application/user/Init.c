/**************************************************** **************************
* File Name          : Init.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 1/20/2016
* Description        : Hardware Configuration & Setup
********************************************************************************
*/
#include "Includes.h"


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
* PCLK2_FRE£º 28000000
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
#endif

void Init_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
 
#if ( UART2_EN > 0U )      
    // Enable the USART2 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if ( UART3_EN > 0U )     
      // Enable the USART3 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if ( UART4_EN > 0U )     
      // Enable the USART4 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if ( UART1_EN > 0U )  
     // Enable the USART1 Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);     
#endif    

#if ( TIM2_EN > 0U )  
    // Enable the TIM2 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 8;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif

#if ( TIM3_EN > 0U )      
    // Enable the TIM3 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif
    
#if ( TIM4_EN > 0U )      
    // Enable the TIM4 global Interrupt 
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 10;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
#endif 
    
#if( WDG_EN > 0u  )
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 11;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);    
#endif     
    
}

void Init_Stm32( void )
{
#if ( UART1_EN > 0U )      
    UART_Init( st_Uart1,PORT_UART1, UART_BDR9600 );
    UART1_Put("USART1 Init OK! \r\n",sizeof( "USART1 Init OK! \r\n" ));
#endif

#if ( UART2_EN > 0U )          
    UART_Init( st_Uart2,PORT_UART2, UART_BDR115200);
    UART2_Put("USART2 Init OK! \r\n",sizeof( "USART2 Init OK! \r\n" ));
#endif 

#if ( UART4_EN > 0U )          
    UART_Init( st_Uart4,PORT_UART4, UART_BDR115200);
   // UART4_Put("USART4 Init OK! \r\n",sizeof( "USART4 Init OK! \r\n" ));
#endif     

#if ( UART3_EN > 0U )          
    UART_Init( st_Uart3,PORT_UART3, UART_BDR115200);
    UART3_Put("USART3 Init OK! \r\n",sizeof( "USART3 Init OK! \r\n" ));
#endif 
    
#if( WDG_EN > 0u  ) 
    WDG_Init();
#endif
    Init_NVIC_Configuration();   
}

static void Init_Devices( void )
{
    Board_Init();
}

void Init_System( void )
{    
    Init_RCC_Configuration();
    Init_Stm32();
    if (SysTick_Config(SystemFrequency / 1000))       /* Setup SysTick Timer for 1 msec interrupts  */
    { 
        /* Capture error */ 
        while (1);
    }
    Init_Devices();
}

/* EOF */