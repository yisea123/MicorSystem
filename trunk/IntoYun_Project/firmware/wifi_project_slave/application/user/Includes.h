#ifndef __INCLUDES_H
#define __INCLUDES_H
/*
********************************************************************************
*                                         STANDARD LIBRARIES
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
/*
********************************************************************************
*                        LIBRARIES
********************************************************************************
*/
#include "stm32f10x.h"
#include "Util.h"
#include "Util.h"
#include "TM_util.h"
/*
********************************************************************************
*                         STM32F10X_Driver
********************************************************************************
*/
#include "Stm32hal.h"
#include "USART.h"
#include "WDG.h"
#include "ADC.h"
#include "RTC.h"
#include "SPIx.h"
#include "Timer.h"
/*
********************************************************************************
*                         Application 
********************************************************************************
*/
#include "Init.h"
#include "board.h"
#include "SysCfg.h"
#include "state.h"
#include "Ctrl_Dev.h"


#endif /* __INCLUDES_H */