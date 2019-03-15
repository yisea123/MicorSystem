/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    apps_UploadSht20.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/07/12
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef _APPS_UPLOADSHT20_H
#define _APPS_UPLOADSHT20_H

typedef struct{
   int32_t sht2x_Temp;
   int32_t sht2x_Hum;
   int32_t uploadInterval;
}apps_sht2x;

extern apps_sht2x st_apps_sht2x;

void UploadSht20_Action( int count  );
void UploadSht20_SetInterval( int32_t uploadInterval );

#endif  /* _APPS_DOWNLOAD_H */