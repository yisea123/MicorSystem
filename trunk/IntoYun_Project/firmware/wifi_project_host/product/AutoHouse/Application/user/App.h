/** \file

$Id: app.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __APP_H
#define __APP_H

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
#define STM32RES_GOT                0x0001
#define FPGACM3_GOT                 0x0002

#define COMM_CAN1CTRLREQ            0x0001
#define COMM_CAN1CTRLRSP            0x0002
#define COMM_UART1                  0x0004
#define COMM_UART2                  0x0008
#define COMM_UART3                  0x0010
#define COMM_I2C                    0x0020
#define COMM_CAN1                   0x0040
#define COMM_UART4                  0x0080


#endif /* __APP_H*/