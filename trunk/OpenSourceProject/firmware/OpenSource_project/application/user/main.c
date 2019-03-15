/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    main.c
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
**/
#include "Includes.h"
#include "user_Intoyun.h"

int main(void)
{
    Init_System();
    System.init();
    userInit();
    while (1)
    {
        System.loop();
        IntoYunuserHandle();
    }
}

/* end of this file  */

