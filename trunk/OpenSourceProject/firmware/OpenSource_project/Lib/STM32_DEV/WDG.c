/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    wdg.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
*/
#include "includes.h"

void WDG_Init( void )
{
    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
    
    /* WWDG clock counter = (PCLK1/4096)/8 = 1099 Hz (~910 µs)  */
    WWDG_SetPrescaler(WWDG_Prescaler_8);
    
    /* Set Window value to 65 */
    WWDG_SetWindowValue(65);
    
    /* Enable WWDG and set counter value to 127, WWDG timeout = ~910 µs * 64 = 58.25 ms */
    WWDG_Enable(127);
    
    /* Clear EWI flag */
    WWDG_ClearFlag();
    
    /* Enable EW interrupt */
   // WWDG_EnableIT();

}

void Feed_DisWatchDog( void )
{
     MSG* msg = (MSG*)&st_SysMsg; 
     
     msg->CommFlags_bit.WDTCTRL = 0;
}

void Feed_Dog( void )
{
    static INT8U u8_flag=0;
    MSG* msg = (MSG*)&st_SysMsg; 
    
    if( msg->CommFlags_bit.WDTCTRL )
    {
        if( u8_flag ) 
        {
              u8_flag = 0;
        }
        else 
        {

              u8_flag = 1;
        }
    }
}

void Feed_FPGA( void )
{
  
}

/* EOF */