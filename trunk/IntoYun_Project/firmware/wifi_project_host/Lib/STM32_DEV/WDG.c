/*******************************************************************************
** File name:	 wdg.c
** Created by:	 Mingfei Tang		
** Created date: 2016/1/20		
** Version:	 V1.00			
** Descriptions:
**
**------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*******************************************************************************/
#include "includes.h"

static void IWDG_Init( uint8_t prer, uint16_t rlr ) ;

void WDG_Init( void )
{
    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    
    /* WWDG clock counter = (PCLK1/4096)/8 = 1099 Hz (~910 �s)  */
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    
    /* Set Window value to 65 */
    WWDG_SetWindowValue(65);
    
    /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 �s * 64 = 58.25 ms */
    WWDG_Enable(127);
    
    /* Clear EWI flag */
    WWDG_ClearFlag();
    
    /* Enable EW interrupt */
   // WWDG_EnableIT();

}

/*
     Tout=64*625/40=1000ms
*/
void Iwdg_Init( void )
{
    NVIC_InitTypeDef NVIC_InitStructure;
    
    IWDG_Init( 4, 625 );

    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 9;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;    
    NVIC_Init(&NVIC_InitStructure);      
}

static void IWDG_Init( uint8_t prer, uint16_t rlr )
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //①使能对寄存器 I 写操作
    IWDG_SetPrescaler(prer);                        //②设置 IWDG 预分频值:设置 IWDG 预分频值
    IWDG_SetReload(rlr);                           //②设置 IWDG 重装载值
    IWDG_ReloadCounter();                          //③按照 IWDG 重装载寄存器的值重装载 IWDG 计数器
    IWDG_Enable();                                 //④使能 IWDG
}

void IWDG_Feed(void)
{
    IWDG_ReloadCounter();
}


/* EOF */