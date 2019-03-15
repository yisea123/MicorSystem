/** \file

$Id: SysCfg.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __SYSCFG_H
#define __SYSCFG_H

/***** Firmware Version Number *************************************************
   Version Number Format
   [VER_MAJOR].[VER_MINOR][VER_BUILD].[VER_TEST][VER_PATCH]
   Example: V1.00A
*******************************************************************************/
#define  VER_MAJOR                       1
#define  VER_MINOR                       20
#define  VER_BUILD                       0
#define  VER_PATCH                       ' '

#define  WDG_EN                                                 0u
#define  TIM2_EN                                                1u 
#define  TIM3_EN                                                0u 
#define  TIM4_EN                                                0u 
#define  UART1_EN                                               1u
#define  UART2_EN                                               1u
#define  UART3_EN                                               1u
#define  UART4_EN                                               1u
#define  UART5_EN                                               1u

#endif /* __SYSCFG_H */
