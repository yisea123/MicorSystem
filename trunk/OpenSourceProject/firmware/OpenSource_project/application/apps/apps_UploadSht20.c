/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    apps_UploadSht20.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/07/12
  * @brief   McsParser ctrl interface
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#include "Includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
apps_sht2x st_apps_sht2x; 

/* Private function prototypes -----------------------------------------------*/
void UploadSht20_Action( int count )
{
  int8_t data[4];
  
  if( st_apps_sht2x.uploadInterval > 0 )
  {
      if((count % st_apps_sht2x.uploadInterval) == 0 )
      {
          sht2xdrv_GetTemp( &st_apps_sht2x.sht2x_Temp );
          sht2xdrv_GetRH( &st_apps_sht2x.sht2x_Hum );
          data[0] = (int8_t)(st_apps_sht2x.sht2x_Temp >>8);
          data[1] = (int8_t)(st_apps_sht2x.sht2x_Temp );
          
          data[2] = (int8_t)(st_apps_sht2x.sht2x_Hum >>8);
          data[3] = (int8_t)(st_apps_sht2x.sht2x_Hum );
          vApps_UploadSht20Value( data );
      }
  }
}

void UploadSht20_SetInterval( int32_t uploadInterval )
{
  st_apps_sht2x.uploadInterval = uploadInterval;
}



/* End of this file */


