/**
  ******************************************************************************
  *                     (c) Copyright 2015, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    iap.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2015/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef __IAP_H
#define __IAP_H

void FLASH_If_Init(void);
INT8U IAP_FlashProgram( INT32U WriteAddr,INT8U *pRbuff, INT32U len );

#endif /* __IAP_H */