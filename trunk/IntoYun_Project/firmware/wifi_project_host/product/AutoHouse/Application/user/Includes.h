/** \file

$Id: Includes.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __INCLUDES_H
#define __INCLUDES_H
/*
********************************************************************************
*                        STANDARD LIBRARIES
********************************************************************************
*/
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "TypeDef.h"
#include "App.h"
#include "SysCfg.h"
/*
********************************************************************************
*                        LIBRARIES
********************************************************************************
*/
#include "stm32f10x.h"
#include "Util.h"
#include "TM_util.h"

/*
********************************************************************************
*                        STM32F10X_Driver
********************************************************************************
*/
#include "Stm32hal.h"
#include "USART.h"
#include "WDG.h"
#include "ADC.h"
#include "RTC.h"
#include "SPIx.h"
#include "Timer.h"
#include "IAP.h"

/*
********************************************************************************
*                         board
********************************************************************************
*/
#include "board.h"
#include "WQ25XX.h"

/*
********************************************************************************
*                         intoyun
********************************************************************************
*/
#include "project_config.h"
#include "intoyun_interface.h"

/*
********************************************************************************
*                         comm
********************************************************************************
*/
#include "mcs_protocol.h"

/*
********************************************************************************
*                        application
********************************************************************************
*/
#include "apps_Def.h"
#include "apps_InforSave.h"
#include "apps_commHandler.h"

/*
********************************************************************************
*                        user
********************************************************************************
*/
#include "Init.h"
#include "State.h"
#include "user_IntoYun.h"

#endif /* __INCLUDES_H */