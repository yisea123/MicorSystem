/** \file

$Id: main.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "Includes.h"
#include "log.h"

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
int main(void)
{
    Init_System();
    System.init();
    userInit();
    while (1)
    {
        System.loop();
        userHandle();
    }
}

/* EOF */
